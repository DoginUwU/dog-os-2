#include <common.h>
#include <lib/math.h>
#include <lib/memory.h>
#include <stdint.h>

#define PAGE_DIRS_COUNT 256
#define PAGE_FRAMES_COUNT (0x100000000 / PAGE_SIZE / 8)

static uint32_t page_frame_min;
static uint32_t page_frame_max;
static uint32_t total_allocated;

static uint32_t page_dirs[PAGE_DIRS_COUNT][1024] __attribute__((aligned(4096)));
static uint8_t page_dirs_used[PAGE_DIRS_COUNT];
int memory_num_virtual_pages;

// TODO: Make length dynamic
uint8_t physical_memory_bitmap[PAGE_FRAMES_COUNT / 8];

void invalidate(uint32_t virtual_address);

void init_pmm(uint32_t memory_low, uint32_t memory_high) {
  page_frame_min = CEIL_DIV(memory_low, PAGE_SIZE);
  page_frame_max = memory_high / PAGE_SIZE;
  total_allocated = 0;

  memory_set(physical_memory_bitmap, 0, sizeof(physical_memory_bitmap));
}

uint32_t pmm_allocation_page_frame() {
  uint32_t start = page_frame_min / 8 + ((page_frame_min & 7) != 0 ? 1 : 0);
  uint32_t end = page_frame_max / 8 - ((page_frame_max & 7) != 0 ? 1 : 0);

  for (uint32_t b = start; b < end; b++) {
    uint8_t byte = physical_memory_bitmap[b];

    if (byte == 0xFF) {
      continue;
    }

    for (uint32_t i = 0; i < 8; i++) {
      int used = byte >> i & 1;

      if (used == 0) {
        byte ^= (-1 ^ byte) & (1 << i); // Reverse byte to be used
        physical_memory_bitmap[b] = byte;
        total_allocated++;

        uint32_t address = (b * 8 * i) * PAGE_SIZE;
        return address;
      }
    }
  }

  return 0;
}

void memory_change_page_dir(uint32_t *page_directory) {
  page_directory = (uint32_t *)(((uint32_t)page_directory) - KERNEL_ADDRESS);

  asm volatile("mov %0, %%eax \n mov %%eax, %%cr3 \n" ::"m"(page_directory));
}

uint32_t *memory_get_current_page_dir() {
  uint32_t page_dir;

  asm volatile("mov %%cr3, %0" : "=r"(page_dir));
  page_dir += KERNEL_ADDRESS;

  return (uint32_t *)page_dir;
}

void sync_page_dirs() {
  for (size_t i = 0; i < PAGE_DIRS_COUNT; i++) {
    if (page_dirs_used[i]) {
      uint32_t *page_directory = page_dirs[i];

      for (size_t i2 = 768; i2 < 1023; i2++) {
        page_directory[i2] = initial_page_dir[i2] & ~PAGE_FLAG_OWNER;
      }
    }
  }
}

void memory_map_page(uint32_t virtual_address, uint32_t physical_address,
                     uint32_t flags) {
  uint32_t *previous_page_dir = 0;

  if (virtual_address >= KERNEL_ADDRESS) {
    previous_page_dir = memory_get_current_page_dir();

    if (previous_page_dir != initial_page_dir) {
      memory_change_page_dir(initial_page_dir);
    }
  }

  uint32_t page_directory_index = virtual_address >> 22;
  uint32_t page_table_index = virtual_address >> 12 & 0x3FF;

  uint32_t *page_directory = REC_PAGE_DIR;
  uint32_t *page_table = REC_PAGE_TABLE(page_directory_index);

  if (!(page_directory[page_directory_index] & PAGE_FLAG_PRESENT)) {
    uint32_t page_table_address = pmm_allocation_page_frame();
    page_directory[page_directory_index] = page_table_address |
                                           PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE |
                                           PAGE_FLAG_OWNER | flags;
    invalidate(virtual_address);

    for (uint32_t i = 0; i < 1024; i++) {
      page_table[i] = 0;
    }
  }

  page_table[page_table_index] = physical_address | PAGE_FLAG_PRESENT | flags;
  memory_num_virtual_pages++;
  invalidate(virtual_address);

  if (previous_page_dir != 0) {
    sync_page_dirs();

    if (previous_page_dir != initial_page_dir) {
      memory_change_page_dir(previous_page_dir);
    }
  }
}

void init_memory(uint32_t memory_high, uint32_t physical_allocation_start) {
  memory_num_virtual_pages = 0;
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
