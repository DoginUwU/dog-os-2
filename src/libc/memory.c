#include "memory.h"

void memory_copy(char *source, char *dest, int nbytes) {
  for (int i = 0; i < nbytes; i++) {
    *(dest + i) = *(source + i);
  }
}

void memory_set(void *dest, u8 val, u32 len) {
  u8 *temp = dest;

  for (; len > 0; len--) {
    *temp++ = val;
  }
}

// Hardcoded from now, needed to be computed in link time
u32 free_mem_addr = 0x10000;

u32 malloc(u32 size, int align, u32 *addr) {
  if (align == 1 && (free_mem_addr & 0xFFFF000)) {
    free_mem_addr &= 0xFFFF000;
    free_mem_addr += 0x1000;
  }

  if (addr)
    *addr = free_mem_addr;

  u32 ret = free_mem_addr;
  free_mem_addr += size;

  return ret;
}
