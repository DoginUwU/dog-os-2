#include "memory/physical_memory_manager.h"
#include "drivers/screen.h"
#include "memory/memory.h"
#include <stdint.h>

extern uint32_t kernel_virtual_start;

uint8_t *phyisical_bitmap;
size_t total_pages = 0;
int physical_memory_manager_ready = 0;

void init_physical_memory_manager() {
  total_pages = memory_map.total_size / PAGE_SIZE;

  size_t bitmap_size = align_up(total_pages, 8) / 8;
  phyisical_bitmap = kmalloc(bitmap_size);

  memory_set(phyisical_bitmap, 0, bitmap_size);

  // Check reserved memory regions as used
  for (size_t i = 0; i < memory_map.count; i++) {
    memory_region_t *region = &memory_map.regions[i];

    if (region->type == MEMORY_REGION_RESERVED) {
      size_t start_page = region->addr / PAGE_SIZE;
      size_t end_page = (region->addr + region->len) / PAGE_SIZE;

      for (size_t j = start_page; j < end_page; j++) {
        set_page_used(j);
      }
    }
  }

  // Check kernel region as used
  size_t start_kernel = (size_t)&kernel_virtual_start / PAGE_SIZE;
  size_t end_kernel = (size_t)placement_address / PAGE_SIZE;
  for (size_t j = start_kernel; j < end_kernel; j++) {
    set_page_used(j);
  }

  physical_memory_manager_ready = 1;

  println("Total pages: %d", total_pages);
}

void set_page_used(size_t page_index) {
  phyisical_bitmap[page_index / 8] |= (1 << (page_index % 8));
}

void set_page_free(size_t page_index) {
  phyisical_bitmap[page_index / 8] &= ~(1 << (page_index % 8));
}

int is_page_free(size_t page_index) {
  return !(phyisical_bitmap[page_index / 8] & (1 << (page_index % 8)));
}

void *allocate_pages(size_t num_pages) {
  size_t consecutive_free_pages = 0;
  size_t start_page_index = 0;

  for (size_t i = 0; i < total_pages; i++) {
    if (is_page_free(i)) {
      if (consecutive_free_pages == 0) {
        start_page_index = i;
      }

      consecutive_free_pages++;

      if (consecutive_free_pages == num_pages) {
        for (size_t j = start_page_index; j < start_page_index + num_pages;
             j++) {
          set_page_used(j);
        }

        return (void *)(start_page_index * PAGE_SIZE);
      }
    } else {
      consecutive_free_pages = 0;
    }
  }

  return NULL;
}

void free_pages(void *address, size_t num_pages) {
  if (num_pages == 0) {
    return;
  }

  size_t start = (size_t)address / PAGE_SIZE;
  size_t end = start + num_pages;

  for (size_t i = start; i < end; i++) {
    set_page_free(i);
  }
}
