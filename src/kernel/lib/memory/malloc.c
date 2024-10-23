#include <common.h>
#include <lib/math.h>
#include <lib/memory/malloc.h>
#include <lib/memory/virtual_memory_manager.h>
#include <stdint.h>

extern uint32_t kernel_virtual_end;
uint32_t placement_address = (uint32_t)&kernel_virtual_end;

void *malloc(const size_t size) {
  void *ptr = 0;

  asm volatile("int $0x80" ::"a"(3), "b"(size));
  asm volatile("movl %%eax, %0" : "=r"(ptr));

  return ptr;
}

void free(const void *ptr) { asm volatile("int $0x80" ::"a"(4), "b"(ptr)); }

void *kmalloc_internal(size_t size, int align, uint32_t *physical_address) {
  if (align == 1 && (placement_address & 0xFFFFF000)) {
    placement_address &= 0xFFFFF000;
    placement_address += PAGE_SIZE;
  }

  if (physical_address) {
    *physical_address = placement_address;
  }

  uint32_t temp = placement_address;
  placement_address += size;
  return (void *)temp;
}

void *kmalloc(size_t size) { return kmalloc_internal(size, 0, 0); }
void *kmalloc_align(size_t size) { return kmalloc_internal(size, 1, 0); }
void *kmalloc_align_pysical(size_t size, uint32_t *physical_address) {
  return kmalloc_internal(size, 1, physical_address);
}
