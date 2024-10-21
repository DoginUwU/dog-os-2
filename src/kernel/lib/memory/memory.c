#include <common.h>
#include <cpu/idt.h>
#include <drivers/screen.h>
#include <lib/math.h>
#include <lib/memory/kmalloc.h>
#include <lib/memory/memory.h>
#include <panic.h>
#include <stdint.h>

void setup_paging() {}

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

void *align_up(void *ptr, uint32_t align) {
  return (void *)(((uint32_t)ptr + align - 1) & ~(align - 1));
}
