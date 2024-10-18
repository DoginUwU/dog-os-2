#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 0x1000
#define REC_PAGE_DIR ((uint32_t *)0xFFFFF000)
#define REC_PAGE_TABLE(i) ((uint32_t *)(0xFFC00000 + ((i) << 12)))
#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_WRITE (1 << 1)
#define PAGE_FLAG_OWNER (1 << 9)

extern uint32_t initial_page_dir[1024];

void init_memory(uint32_t memory_high, uint32_t physical_allocation_start);
uint32_t pmm_allocation_page_frame();
void memory_map_page(uint32_t virtual_address, uint32_t physical_address,
                     uint32_t flags);

void memory_copy(uint8_t *src, uint8_t *dest, size_t count);
void *memory_set(void *dest, int val, size_t count);

#endif
