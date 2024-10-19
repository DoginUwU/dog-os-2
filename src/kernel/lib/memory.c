#include <common.h>
#include <drivers/screen.h>
#include <lib/math.h>
#include <lib/memory.h>
#include <stdint.h>

uint32_t page_directory[PAGE_ENTRIES] __attribute__((aligned(4096)));
uint32_t first_page_table[PAGE_ENTRIES] __attribute__((aligned(4096)));

void init_paging(multiboot_info_t *boot_info) {
  uint32_t total_memory = (boot_info->mem_upper + 1024) * 1024;
  uint32_t num_pages = total_memory / PAGE_SIZE;

  /*uint32_t *page_directory = (uint32_t *)*/

  for (size_t i = 0; i < PAGE_ENTRIES; i++) {
    page_directory[i] = 0x00000002;
  }

  for (size_t i = 0; i < PAGE_ENTRIES; i++) {
    first_page_table[i] = (i * PAGE_SIZE) | PAGE_FLAG_PRESENT | PAGE_FLAG_RW;
  }
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
