#include <common.h>
#include <lib/math.h>
#include <lib/memory/kmalloc.h>
#include <lib/memory/memory.h>
#include <stdint.h>

extern uint32_t _kernel_end;
uint32_t placement_address = (uint32_t)&_kernel_end;

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

void *kmalloc(size_t size) {
  static uint32_t placement_address_test = KERNEL_MALLOC;

  uint32_t num_pages = (size / PAGE_SIZE) + 1;

  for (uint32_t i = 0; i < num_pages; i++) {
    uint32_t physical_page = allocate_physical_page();
    if (physical_page == 0) {
      return 0;
    }

    map_page(initial_page_dir, placement_address, physical_page,
             PAGE_FLAG_PRESENT | PAGE_FLAG_RW);
    placement_address += PAGE_SIZE;
  }

  return (void *)(placement_address - (num_pages * PAGE_SIZE));
}
void *kmalloc_align(size_t size) { return kmalloc_internal(size, 1, 0); }
void *kmalloc_align_pysical(size_t size, uint32_t *physical_address) {
  return kmalloc_internal(size, 1, physical_address);
}
