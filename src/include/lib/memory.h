#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_WRITE (1 << 1)

extern uint32_t initial_page_dir[1024];

void init_memory(uint32_t memory_high, uint32_t physical_allocation_start);

void memory_copy(uint8_t *src, uint8_t *dest, size_t count);
void *memory_set(void *dest, int val, size_t count);
uint32_t malloc(size_t size);
uint32_t malloc_align(size_t size);
uint32_t malloc_physical(size_t size, uint32_t *physical_address);
uint32_t malloc_align_physical(size_t size, uint32_t *physical_address);

#endif
