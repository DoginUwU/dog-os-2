#include <common.h>
#include <lib/kmalloc.h>
#include <lib/math.h>
#include <lib/memory.h>
#include <stdint.h>

void *kmalloc(size_t size) {
  size = (size + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);

  uint32_t num_pages = size / PAGE_SIZE;

  uint32_t physical_address = pmm_allocation_page_frame();
  if (physical_address == 0) {
    return NULL;
  }

  uint32_t virtual_address = (uint32_t)kmalloc(num_pages * PAGE_SIZE);
  if (virtual_address == 0) {
    return NULL;
  }

  for (uint32_t i = 0; i < num_pages; i++) {
    memory_map_page(virtual_address + (i * PAGE_SIZE),
                    physical_address + (i * PAGE_SIZE), 0);
  }

  return (void *)virtual_address;
}
