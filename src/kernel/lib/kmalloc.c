#include <common.h>
#include <lib/kmalloc.h>
#include <lib/math.h>
#include <lib/memory.h>
#include <stdint.h>

extern uint32_t _kernel_end;
uint32_t placement_address = (uint32_t)&_kernel_end;

void *kmalloc(size_t size, int align) {
  if (align == 1 && (placement_address & 0xFFFFF000)) {
    placement_address &= 0xFFFFF000;
    placement_address += PAGE_SIZE;
  }

  uint32_t temp = placement_address;
  placement_address += size;
  return (void *)temp;
}
