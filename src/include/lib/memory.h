#ifndef MEMORY_H
#define MEMORY_H

#include <multiboot.h>
#include <stddef.h>
#include <stdint.h>

#define PAGE_ENTRIES 1024
#define PAGE_SIZE 0x1000

#define PAGE_FLAG_PRESENT 0x1
#define PAGE_FLAG_RW 0x2
#define PAGE_FLAG_USER 0x4

/*void init_memory(uint32_t physical_allocation_start);*/
void init_paging(multiboot_info_t *boot_info);

void memory_copy(uint8_t *src, uint8_t *dest, size_t count);
void *memory_set(void *dest, int val, size_t count);

#endif
