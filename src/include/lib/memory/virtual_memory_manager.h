#ifndef VIRTUAL_MEMORY_MANAGER_H
#define VIRTUAL_MEMORY_MANAGER_H

#include <stdint.h>

#define PAGE_SIZE 0x1000 // 4kb
#define PAGES_PER_TABLE 1024
#define PAGES_PER_DIRECTORY 1024

#define PAGE_DIRECTORY_INDEX(address) ((address) >> 22)
#define PAGE_TABLE_INDEX(address)                                              \
  (((address) >> 12) & 0x3FF) // max is 1023 = 0x3FF
#define GET_FRAME(directory_entry)                                             \
  ((*directory_entry) &                                                        \
   ~0xFFF) // Remove lowest 12 bits for return frame address
#define SET_ATTRIBUTE(entry, attribute) (*entry |= attribute)
#define CLEAR_ATTRIBUTE(entry, attribute) (*entry &= ~attribute)
#define TEST_ATTRIBUTE(entry, attribute) (*entry & attribute)
#define SET_FRAME(entry, address)                                              \
  (*entry = (*entry & ~0x7FFFF000) | address) // Only set frame, not attributes

typedef enum {
  PTE_PRESENT = 1 << 0,
  PTE_READ_WRITE = 1 << 1,
  PTE_USER = 1 << 2,
  PTE_WRITE_THROUGH = 1 << 3,
  PTE_CACHE_DISABLED = 1 << 4,
  PTE_ACCESSED = 1 << 5,
  PTE_DIRTY = 1 << 6,
  PTE_PAT = 1 << 7,
  PTE_GLOBAL = 1 << 8,
  PTE_FRAME = 0x7FFFF000 // 12 bit shift
} PAGE_TABLE_FLAGS;

typedef enum {
  PDE_PRESENT = 1 << 0,
  PDE_READ_WRITE = 1 << 1,
  PDE_USER = 1 << 2,
  PDE_WRITE_THROUGH = 1 << 3,
  PDE_CACHE_DISABLED = 1 << 4,
  PDE_ACCESSED = 1 << 5,
  PDE_DIRTY = 1 << 6,     // 4MB entry only
  PDE_PAGE_SIZE = 1 << 7, // 0 = 4KB, 1 = 4MB
  PDE_GLOBAL = 1 << 8,    // 4MB entry only
  PDE_PAT = 1 << 9,       // 4MB entry only
  PDE_FRAME = 0x7FFFF000  // 12 bit shift
} PAGE_DIRECTORY_FLAGS;

typedef uint32_t page_table_entry;
typedef uint32_t page_directory_entry;
typedef uint32_t physical_address;
typedef uint32_t virtual_address;

typedef struct {
  page_table_entry entries[PAGES_PER_TABLE];
} page_table_t;

typedef struct {
  page_directory_entry entries[PAGES_PER_DIRECTORY];
} page_directory_t;

extern page_directory_t *current_page_directory;
extern physical_address current_page_directory_address;

page_table_entry *get_page_table_entry(page_table_t *page_table,
                                       const virtual_address address);
page_directory_entry *get_page_directory_entry(page_directory_t *page_directory,
                                               const virtual_address address);
page_table_entry *get_page(const virtual_address address);

void *allocate_page(page_table_entry *page_entry);

#endif
