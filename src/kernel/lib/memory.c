#include <common.h>
#include <lib/memory.h>
#include <math.h>

#define PAGE_SIZE 0x1000
#define PAGE_DIRS_COUNT 256
#define PAGE_FRAMES_COUNT (0x100000000 / PAGE_SIZE / 8)

uint32_t free_mem_addr = 0x10000;

static uint32_t page_frame_min;
static uint32_t page_frame_max;
static uint32_t total_allocated;

static uint32_t page_dirs[PAGE_DIRS_COUNT][1024] __attribute__((aligned(4096)));
static uint8_t page_dirs_used[PAGE_DIRS_COUNT];

// TODO: Make length dynamic
uint8_t physical_memory_bitmap[PAGE_FRAMES_COUNT / 8];

void invalidate(uint32_t virtual_address);

void init_pmm(uint32_t memory_low, uint32_t memory_high) {
  page_frame_min = CEIL_DIV(memory_low, PAGE_SIZE);
  page_frame_max = memory_high / PAGE_SIZE;
  total_allocated = 0;

  memory_set(physical_memory_bitmap, 0, sizeof(physical_memory_bitmap));
}

void init_memory(uint32_t memory_high, uint32_t physical_allocation_start) {
  initial_page_dir[0] = 0;
  invalidate(0);
  initial_page_dir[1023] = ((uint32_t)initial_page_dir - KERNEL_ADDRESS) |
                           PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE;
  invalidate(0xFFFFF000);

  init_pmm(physical_allocation_start, memory_high);

  memory_set(page_dirs, 0, PAGE_SIZE * PAGE_DIRS_COUNT);
  memory_set(page_dirs_used, 0, PAGE_DIRS_COUNT);
}

void invalidate(uint32_t virtual_address) {
  asm volatile("invlpg %0" ::"m"(virtual_address));
}

void memory_copy(uint8_t *src, uint8_t *dest, size_t count) {
  for (size_t i = 0; i < count; i++) {
    *(dest + i) = *(src + i);
  }
}

void *memory_set(void *dest, int val, size_t count) {
  unsigned char *temp = (unsigned char *)dest;

  for (size_t i = 0; i < count; i++) {
    temp[i] = val;
  }

  return dest;
}

uint32_t internal_malloc(size_t size, int align, uint32_t *physical_address) {
  if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
    free_mem_addr &= 0xFFFFF000;
    free_mem_addr += 0x1000;
  }

  if (physical_address) {
    *physical_address = free_mem_addr;
  }

  uint32_t temp = free_mem_addr;
  free_mem_addr += size;

  return temp;
}

uint32_t malloc(size_t size) { return internal_malloc(size, 0, NULL); }
uint32_t malloc_align(size_t size) { return internal_malloc(size, 1, NULL); }
uint32_t malloc_physical(size_t size, uint32_t *physical_address) {
  return internal_malloc(size, 0, physical_address);
}
uint32_t malloc_align_physical(size_t size, uint32_t *physical_address) {
  return internal_malloc(size, 1, physical_address);
}
