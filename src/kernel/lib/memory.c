#include <lib/memory.h>

uint32_t free_mem_addr = 0x10000;

void memory_copy(uint8_t *src, uint8_t *dest, size_t count) {
  for (int i = 0; i < count; i++) {
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

uint32_t internal_malloc(size_t size, int align, uint32_t *physical_address) {
  if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
    free_mem_addr &= 0xFFFFF000;
    free_mem_addr += 0x1000;
  }

  if (physical_address) {
    *physical_address = free_mem_addr;
  }

  uint32_t temp = free_mem_addr;
  free_mem_addr += size;

  return temp;
}

uint32_t malloc(size_t size) { return internal_malloc(size, 0, NULL); }
uint32_t malloc_align(size_t size) { return internal_malloc(size, 1, NULL); }
uint32_t malloc_physical(size_t size, uint32_t *physical_address) {
  return internal_malloc(size, 0, physical_address);
}
uint32_t malloc_align_physical(size_t size, uint32_t *physical_address) {
  return internal_malloc(size, 1, physical_address);
}
