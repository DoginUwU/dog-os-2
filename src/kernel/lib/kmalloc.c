#include <common.h>
#include <lib/kmalloc.h>
#include <lib/math.h>
#include <lib/memory.h>

static uint32_t heap_start;
static uint32_t heap_size;
static uint32_t threshold;
static int kmalloc_initialized = 0;

void change_heap_size(uint32_t new_size);

void kmalloc_init(uint32_t initial_heap_size) {
  heap_start = KERNEL_MALLOC;
  heap_size = 0;
  threshold = 0;
  kmalloc_initialized = 1;

  change_heap_size(initial_heap_size);
}

void change_heap_size(uint32_t new_size) {
  uint32_t old_page_top = CEIL_DIV(heap_size, PAGE_SIZE);
  uint32_t new_Page_top = CEIL_DIV(new_size, PAGE_SIZE);

  uint32_t diff = new_Page_top - old_page_top;

  for (size_t i = 0; i < diff; i++) {
    uint32_t physical_loc = pmm_allocation_page_frame();
    memory_map_page(KERNEL_MALLOC + old_page_top * PAGE_SIZE + i * PAGE_SIZE,
                    physical_loc, PAGE_FLAG_WRITE);
  }
}
