#include <common.h>
#include <cpu/idt.h>
#include <drivers/screen.h>
#include <lib/math.h>
#include <lib/memory/kmalloc.h>
#include <lib/memory/memory.h>
#include <panic.h>
#include <stdint.h>

void setup_paging() { memory_set(physical_bitmap, 0, sizeof(physical_bitmap)); }

uint32_t allocate_physical_page() {
  for (int i = 0; i < PAGE_ENTRIES; i++) {
    if (!(physical_bitmap[i / 32] & (1 << (i % 32)))) {
      physical_bitmap[i / 32] |= (1 << (i % 32));

      return i * PAGE_SIZE;
    }
  }

  return 0;
}

void free_physical_page(uint32_t page_addr) {
  uint32_t page_index = page_addr / PAGE_SIZE;

  physical_bitmap[page_index / 32] &= ~(1 << (page_index % 32));
}

void map_page(uint32_t *page_directory, uint32_t virtual_address,
              uint32_t physical_address, uint32_t flags) {
  uint32_t page_dir_index = virtual_address >> 22;
  uint32_t page_table_index = (virtual_address >> 12) & 0x3FF;

  if (!(page_directory[page_dir_index] & PAGE_FLAG_PRESENT)) {
    uint32_t new_page_table = (uint32_t)allocate_physical_page();

    memory_set((void *)new_page_table, 0, PAGE_SIZE);

    page_directory[page_dir_index] = new_page_table | flags | PAGE_FLAG_PRESENT;
  }

  uint32_t *page_table = (uint32_t *)(page_directory[page_dir_index] & ~0xFFF);
  page_table[page_table_index] =
      (physical_address & ~0xFFF) | flags | PAGE_FLAG_PRESENT;
}

void memory_copy(uint8_t *src, uint8_t *dest, size_t count) {
  for (size_t i = 0; i < count; i++) {
    *(dest + i) = *(src + i);
  }
}

void *memory_set(void *dest, int val, size_t count) {
  unsigned char *temp = (unsigned char *)dest;

  for (size_t i = 0; i < count; i++) {
    temp[i] = val;
  }

  return dest;
}
