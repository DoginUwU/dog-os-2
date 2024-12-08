#pragma once

#include <stdint.h>

typedef struct {
  uint32_t addr;
  uint32_t len;
  uint32_t type;
} memory_region_t;

typedef struct {
  memory_region_t *regions;
  uint32_t count;
} memory_map_t;

extern memory_map_t memory_map;

void *kmalloc(uint32_t size);
