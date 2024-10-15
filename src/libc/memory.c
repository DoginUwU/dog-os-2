#include "memory.h"

void memory_copy(char *source, char *dest, int nbytes) {
  for (int i = 0; i < nbytes; i++) {
    *(dest + i) = *(source + i);
  }
}

void memory_set(void *dest, uint8_t val, uint32_t len) {
  uint8_t *temp = dest;

  for (; len > 0; len--) {
    *temp++ = val;
  }
}

// Hardcoded from now, needed to be computed in link time
uint32_t free_mem_addr = 0x10000;

uint32_t malloc(size_t size, int align, uint32_t *addr) {
  if (align == 1 && (free_mem_addr & 0xFFFF000)) {
    free_mem_addr &= 0xFFFF000;
    free_mem_addr += 0x1000;
  }

  if (addr)
    *addr = free_mem_addr;

  uint32_t ret = free_mem_addr;
  free_mem_addr += size;

  return ret;
}
