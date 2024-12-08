#define PAGE_SIZE 4096 // 4KB

#include <stddef.h>

void init_physical_memory_manager();

void set_page_used(size_t page_index);
void set_page_free(size_t page_index);
int is_page_free(size_t page_index);

void *allocate_pages(size_t num_pages);
