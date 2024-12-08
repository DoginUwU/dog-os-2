#include "memory.h"

extern uint32_t kernel_virtual_end;
uint32_t placement_address = (uint32_t)&kernel_virtual_end;
memory_map_t memory_map;

void *kmalloc(uint32_t size) {
  uint32_t temp = placement_address;
  placement_address += size;
  return (void *)temp;
}
