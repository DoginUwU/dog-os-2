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
/*#define PAGE_FLAG_WRITETHROUGH (1 << 3)*/
/*#define PAGE_FLAG_CACHE_DISABLE (1 << 4)*/
#define PAGE_FLAG_ACCESSED (1 << 5)
#define PAGE_FLAG_DIRTY (1 << 6)
#define PAGE_FLAG_4MB (1 << 7)
/*#define PAGE_FLAG_GLOBAL (1 << 8)*/

extern uint32_t *initial_page_dir;

static uint32_t physical_bitmap[PAGE_ENTRIES / 32];

static uint32_t page_directory[1024] __attribute__((aligned(4096)));
static uint32_t page_table[1024] __attribute__((aligned(4096)));

void setup_paging();
uint32_t allocate_physical_page();
void free_physical_page(uint32_t page_addr);
void map_page(uint32_t *page_directory, uint32_t virtual_address,
              uint32_t physical_address, uint32_t flags);

void memory_copy(uint8_t *src, uint8_t *dest, size_t count);
void *memory_set(void *dest, int val, size_t count);
void *align_up(void *ptr, uint32_t align);

#endif
