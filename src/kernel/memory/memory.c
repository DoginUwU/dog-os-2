#include "memory/memory.h"
#include "memory/physical_memory_manager.h"

extern uint32_t kernel_virtual_end;
uint32_t placement_address = (uint32_t)&kernel_virtual_end;
memory_map_t memory_map;

void *kmalloc(uint32_t size) {
  if (physical_memory_manager_ready == 0) {
    uint32_t temp = placement_address;
    placement_address += size;

    return (void *)temp;
  }

  uint32_t aligned_size = align_up(size, PAGE_SIZE);
  uint32_t num_pages = (aligned_size + PAGE_SIZE - 1) / PAGE_SIZE;

  return allocate_pages(num_pages);
}

void kfree(void *address, size_t size) {
  if (physical_memory_manager_ready == 0) {
    return;
  }

  uint32_t aligned_size = align_up(size, PAGE_SIZE);
  uint32_t num_pages = (aligned_size + PAGE_SIZE - 1) / PAGE_SIZE;
  free_pages(address, num_pages);
}

void memory_set(void *dest, int val, size_t count) {
  for (size_t i = 0; i < count; i++) {
    ((unsigned char *)dest)[i] = val;
  }
}

size_t align_up(size_t addr, size_t align) {
  return (addr + (align - 1)) & ~(align - 1);
}
