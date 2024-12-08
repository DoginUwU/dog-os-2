#pragma once

#include <stddef.h>
#include <stdint.h>

enum MemoryRegionType {
  MEMORY_REGION_AVAILABLE = 1,
  MEMORY_REGION_RESERVED = 2,
};

typedef struct {
  uint32_t addr;
  uint32_t len;
  uint8_t type;
} memory_region_t;

typedef struct {
  memory_region_t *regions;
  uint32_t total_size;
  uint32_t count;
} memory_map_t;

extern memory_map_t memory_map;
extern uint32_t placement_address;

void *kmalloc(size_t size);

void memory_set(void *dest, int val, size_t count);
