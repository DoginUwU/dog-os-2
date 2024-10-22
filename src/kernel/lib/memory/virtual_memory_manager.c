#include <common.h>
#include <cpu/idt.h>
#include <cpu/isr.h>
#include <lib/memory/memory.h>
#include <lib/memory/phyisical_memory_manager.h>
#include <lib/memory/virtual_memory_manager.h>
#include <panic.h>
#include <stddef.h>
#include <stdint.h>

page_directory_t *current_page_directory = 0;
/*uint32_t current_page_directory_address = 0;*/

uint32_t *get_page_table_entry(page_table_t *page_table,
                               const uint32_t address) {
  if (page_table) {
    return &page_table->entries[PAGE_TABLE_INDEX(address)];
  }

  return NULL;
}

uint32_t *get_page_directory_entry(page_directory_t *page_directory,
                                   const uint32_t address) {
  if (page_directory) {
    return &page_directory->entries[PAGE_TABLE_INDEX(address)];
  }

  return NULL;
}

uint32_t *get_page(const uint32_t address) {
  // Find page directory
  page_directory_t *page_directory = current_page_directory;

  // Find table in directory
  uint32_t *directory_entry =
      &page_directory->entries[PAGE_DIRECTORY_INDEX(address)];
  page_table_t *page_table = (page_table_t *)GET_FRAME(directory_entry);

  // Find page in table
  uint32_t *page_entry = &page_table->entries[PAGE_TABLE_INDEX(address)];

  return page_entry;
}

void *allocate_page(uint32_t *page_entry) {
  void *block = allocate_blocks(1);

  if (block) {
    SET_FRAME(page_entry, (uint32_t)block);
    SET_ATTRIBUTE(page_entry, PTE_PRESENT);
  }

  return block;
}

void free_page(uint32_t *page_entry) {
  void *address = (void *)GET_FRAME(page_entry);

  if (address) {
    free_blocks(address, 1);
  }

  CLEAR_ATTRIBUTE(page_entry, PTE_PRESENT);
}

int set_page_directory(page_directory_t *page_directory) {
  if (page_directory == NULL) {
    return 0;
  }

  current_page_directory = page_directory;

  asm volatile("movl %%eax, %%cr3" ::"a"(current_page_directory));

  return 1;
}

void flush_tlb_entry(const uint32_t address) {
  asm volatile("cli; invlpg (%0); sti" ::"r"(address));
}

int map_page(void *physical_address, void *virtual_address) {
  page_directory_t *page_directory = current_page_directory;

  uint32_t *page_entry =
      &page_directory->entries[PAGE_DIRECTORY_INDEX((uint32_t)virtual_address)];

  // Allocate a new block if needed
  if (TEST_ATTRIBUTE(page_entry, PTE_PRESENT) != PTE_PRESENT) {
    page_table_t *page_table = (page_table_t *)allocate_blocks(1);

    if (page_table == NULL) {
      return 0;
    }

    memory_set(page_table, 0, sizeof(page_table_t));

    uint32_t *page_entry =
        &page_directory
             ->entries[PAGE_DIRECTORY_INDEX((uint32_t)virtual_address)];

    SET_ATTRIBUTE(page_entry, PDE_PRESENT);
    SET_ATTRIBUTE(page_entry, PDE_READ_WRITE);
    SET_FRAME(page_entry, (uint32_t)page_table);
  }

  page_table_t *page_table = (page_table_t *)GET_FRAME(page_entry);
  uint32_t *page =
      &page_table->entries[PAGE_TABLE_INDEX((uint32_t)virtual_address)];

  SET_ATTRIBUTE(page, PTE_PRESENT);
  SET_FRAME(page, (uint32_t)physical_address);

  return 1;
}

int unmap_page(void *virtual_address) {
  uint32_t *page_table = get_page((uint32_t)virtual_address);
  SET_FRAME(page_table, 0);
  CLEAR_ATTRIBUTE(page_table, PTE_PRESENT);

  return 1;
}

void init_virtual_memory_manager() {
  irq_install_handler(IRQ_PAGE_FAULT, page_fault);

  page_directory_t *page_directory = (page_directory_t *)allocate_blocks(3);

  if (page_directory == NULL) {
    panic("Failed to allocate the initial page_directory");
  }

  memory_set(page_directory, 0, sizeof(page_directory_t));

  for (uint32_t i = 0; i < PAGES_PER_DIRECTORY; i++) {
    page_directory->entries[i] = PDE_READ_WRITE;
  }

  page_table_t *page_table = (page_table_t *)allocate_blocks(1);

  if (page_table == NULL) {
    panic("Failed to allocate the initial page_table");
  }

  // 3GB page table for higher half kernel
  page_table_t *page_table_3G = (page_table_t *)allocate_blocks(1);

  if (page_table_3G == NULL) {
    panic("Failed to allocate the initial page_table_3G");
  }

  memory_set(page_table, 0, sizeof(page_table_t));
  memory_set(page_table_3G, 0, sizeof(page_table_t));

  // Identify first 4MB of memory for kernel
  for (uint32_t i = 0, frame = 0x0, virtual_address = 0x0; i < PAGES_PER_TABLE;
       i++, frame += PAGE_SIZE, virtual_address += PAGE_SIZE) {
    uint32_t page = 0;
    SET_ATTRIBUTE(&page, PTE_PRESENT);
    SET_ATTRIBUTE(&page, PTE_READ_WRITE);
    SET_FRAME(&page, frame);

    page_table_3G->entries[PAGE_TABLE_INDEX(virtual_address)] = page;
  }

  for (uint32_t i = 0, frame = KERNEL_ADDRESS,
                virtual_address = KERNEL_HIGHER_HALF_ADDRESS;
       i < PAGES_PER_TABLE;
       i++, frame += PAGE_SIZE, virtual_address += PAGE_SIZE) {
    uint32_t page = 0;
    SET_ATTRIBUTE(&page, PTE_PRESENT);
    SET_ATTRIBUTE(&page, PTE_READ_WRITE);
    SET_FRAME(&page, frame);

    page_table->entries[PAGE_TABLE_INDEX(virtual_address)] = page;
  }

  uint32_t *page_directory_entry =
      &page_directory
           ->entries[PAGE_DIRECTORY_INDEX(KERNEL_HIGHER_HALF_ADDRESS)];
  SET_ATTRIBUTE(page_directory_entry, PDE_PRESENT);
  SET_ATTRIBUTE(page_directory_entry, PDE_READ_WRITE);
  SET_FRAME(page_directory_entry, (uint32_t)page_table);

  uint32_t *page_directory_entry_3G =
      &page_directory->entries[PAGE_DIRECTORY_INDEX(0x00000000)];
  SET_ATTRIBUTE(page_directory_entry_3G, PDE_PRESENT);
  SET_ATTRIBUTE(page_directory_entry_3G, PDE_READ_WRITE);
  SET_FRAME(page_directory_entry_3G, (uint32_t)page_table_3G);

  /*current_page_directory_address = (uint32_t)&page_directory->entries;*/
  int page_directory_setted = set_page_directory(page_directory);

  if (!page_directory_setted) {
    panic("Failed to change the current page directory");
  }

  asm volatile("movl %cr0, %eax; orl $0x80000001, %eax; movl %eax, %cr0");
}
