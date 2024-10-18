#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

void memory_copy(uint8_t *src, uint8_t *dest, size_t count);
void *memory_set(void *dest, int val, size_t count);
uint32_t malloc(size_t size);
uint32_t malloc_align(size_t size);
uint32_t malloc_physical(size_t size, uint32_t *physical_address);
uint32_t malloc_align_physical(size_t size, uint32_t *physical_address);

#endif
