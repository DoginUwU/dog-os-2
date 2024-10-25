#include <common.h>
#include <cpu/idt.h>
#include <cpu/isr.h>
#include <lib/logging.h>
#include <lib/memory/memory.h>
#include <lib/memory/phyisical_memory_manager.h>
#include <lib/memory/virtual_memory_manager.h>
#include <panic.h>
#include <stddef.h>
#include <stdint.h>

page_directory_t *current_page_directory = 0;

uint32_t *get_page_table_entry(page_table_t *page_table,
                               const uint32_t address) {
  if (page_table == NULL) {
    return NULL;
  }

  return &page_table->entries[PAGE_TABLE_INDEX(address)];
}

uint32_t *get_page_directory_entry(page_directory_t *page_directory,
                                   const uint32_t address) {
  if (page_directory == NULL) {
    return NULL;
  }

  return &page_directory->entries[PAGE_TABLE_INDEX(address)];
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
    *page_entry |= PTE_PRESENT;
  }

  return block;
}

void free_page(uint32_t *page_entry) {
  void *address = (void *)GET_FRAME(page_entry);

  if (address) {
    free_blocks(address, 1);
  }

  *page_entry &= ~PTE_PRESENT;
}

int set_page_directory(page_directory_t *page_directory) {
  if (page_directory == NULL) {
    return 0;
  }

  current_page_directory = page_directory;

  asm volatile("movl %%eax, %%cr3" ::"r"(current_page_directory));

  return 1;
}

void flush_tlb_entry(const uint32_t address) {
  asm volatile("cli; invlpg (%0); sti" ::"r"(address));
}

int map_page(void *physical_address, void *virtual_address) {
  page_directory_t *page_directory = current_page_directory;
  uint32_t directory_index = PAGE_DIRECTORY_INDEX((uint32_t)virtual_address);

  uint32_t *page_entry = &page_directory->entries[directory_index];

  if ((*page_entry & PTE_PRESENT) == 0) {
    page_table_t *page_table = (page_table_t *)allocate_blocks(1);

    if (page_table == NULL) {
      return 0;
    }

    memory_set(page_table, 0, sizeof(page_table_t));

    page_entry = &page_directory->entries[directory_index];
    *page_entry |= PDE_PRESENT | PDE_READ_WRITE;

    SET_FRAME(page_entry, (uint32_t)page_table);
  }

  page_table_t *page_table = (page_table_t *)GET_FRAME(page_entry);
  uint32_t *page =
      &page_table->entries[PAGE_TABLE_INDEX((uint32_t)virtual_address)];

  *page |= PTE_PRESENT;
  SET_FRAME(page, (uint32_t)physical_address);

  return 1;
}

int unmap_page(void *virtual_address) {
  uint32_t *page_table = get_page((uint32_t)virtual_address);
  SET_FRAME(page_table, 0);
  *page_table &= ~PTE_PRESENT;

  return 1;
}

page_table_t *create_page_table(uint32_t address, uint32_t virtual_address,
                                uint16_t flags) {
  page_table_t *page_table = (page_table_t *)allocate_blocks(1);

  if (page_table == NULL) {
    panic("Failed to allocate some page_table");
  }

  memory_set(page_table, 0, sizeof(page_table_t));

  uint32_t current_frame = address;
  uint32_t current_virtual_address = virtual_address;

  for (uint32_t i = 0; i < PAGES_PER_TABLE; i++) {
    uint32_t page = flags;
    SET_FRAME(&page, current_frame);

    page_table->entries[PAGE_TABLE_INDEX(current_virtual_address)] = page;

    current_frame += PAGE_SIZE;
    current_virtual_address += PAGE_SIZE;
  }

  return page_table;
}

void create_and_insert_table(page_directory_t *directory, uint32_t address,
                             uint32_t virtual_address, uint32_t table_flags,
                             uint32_t directory_flags) {
  page_table_t *page_table =
      create_page_table(address, virtual_address, table_flags);

  uint32_t *page_dir_entry =
      &directory->entries[PAGE_DIRECTORY_INDEX(virtual_address)];
  *page_dir_entry |= directory_flags;
  SET_FRAME(page_dir_entry, (uint32_t)page_table);
}

void create_and_insert_tables(page_directory_t *directory,
                              uint32_t start_address, uint32_t end_address,
                              uint32_t table_flags, uint32_t directory_flags) {
  uint32_t current_frame = start_address;
  uint32_t current_virtual_address = start_address;

  for (uint32_t i = 0; i < PAGES_PER_DIRECTORY; i++) {
    create_and_insert_table(directory, current_frame, current_virtual_address,
                            table_flags, directory_flags);

    current_frame += PAGES_PER_TABLE * PAGE_SIZE;
    current_virtual_address += PAGES_PER_TABLE * PAGE_SIZE;

    if (current_virtual_address >= end_address) {
      break;
    }
  }
}

extern uint32_t _kernel_code_start;
extern uint32_t _kernel_code_end;
extern uint32_t _user_code_start;
extern uint32_t _user_stack_end;

void init_virtual_memory_manager() {
  page_directory_t *page_directory = (page_directory_t *)allocate_blocks(3);

  if (page_directory == NULL) {
    panic("Failed to allocate the initial page_directory");
  }

  memory_set(page_directory, 0, sizeof(page_directory_t));

  for (uint32_t i = 0; i < PAGES_PER_DIRECTORY; i++) {
    page_directory->entries[i] = PDE_READ_WRITE;
  }

  log_info("Kernel code start: %x", &_kernel_code_start);
  log_info("Kernel code end: %x", &_kernel_code_end);
  log_info("User code start: %x", &_user_code_start);
  log_info("User stack end: %x", &_user_stack_end);

  create_and_insert_tables(page_directory, 0, 0x400000,
                           PTE_PRESENT | PTE_READ_WRITE,
                           PDE_PRESENT | PDE_READ_WRITE);

  create_and_insert_tables(page_directory, 0x400000, 0x800000,
                           PTE_PRESENT | PTE_READ_WRITE | PTE_USER,
                           PDE_PRESENT | PDE_READ_WRITE | PDE_USER);

  if (!set_page_directory(page_directory)) {
    panic("Failed to change the current page directory");
  }

  asm volatile("movl %cr0, %eax; orl $0x80000001, %eax; movl %eax, %cr0");
}
