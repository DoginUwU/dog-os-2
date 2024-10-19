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
/*#define PAGE_FLAG_4MB (1 << 7)*/
/*#define PAGE_FLAG_GLOBAL (1 << 8)*/

typedef struct {
  uint32_t present : 1;
  uint32_t rw : 1;
  uint32_t user : 1;
  /*uint32_t writethrough : 1;*/
  /*uint32_t cache_disable : 1;*/
  uint32_t accessed : 1;
  uint32_t dirty : 1;
  uint32_t _reserved : 1;
  /*uint32_t global : 1;*/
  uint32_t frame : 20;
} page_t;

typedef struct {
  page_t pages[PAGE_ENTRIES];
} page_table_t;

typedef struct {
  page_table_t *tables[PAGE_ENTRIES];
  uint32_t tables_physical[PAGE_ENTRIES];
  uint32_t physical_address;
} page_directory_t;

void init_paging();
page_t *get_page(uint32_t address, int make, page_directory_t *directory);
void page_fault(registers_t *regs);

void memory_copy(uint8_t *src, uint8_t *dest, size_t count);
void *memory_set(void *dest, int val, size_t count);

#endif
