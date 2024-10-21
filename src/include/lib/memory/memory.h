#ifndef MEMORY_H
#define MEMORY_H

#include <cpu/isr.h>
#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 0x1000 // 4KB
#define PAGE_ENTRIES 1024

#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_RW (1 << 1)
#define PAGE_FLAG_USER (1 << 2)
#define PAGE_FLAG_ACCESSED (1 << 5)
#define PAGE_FLAG_DIRTY (1 << 6)
#define PAGE_FLAG_4MB (1 << 7)

extern uint32_t *initial_page_directory;

void memory_copy(uint8_t *src, uint8_t *dest, size_t count);
void *memory_set(void *dest, int val, size_t count);
void *align_up(void *ptr, uint32_t align);

#endif
