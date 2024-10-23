#include <common.h>
#include <drivers/screen.h>
#include <lib/logging.h>
#include <lib/memory/memory.h>
#include <lib/memory/phyisical_memory_manager.h>
#include <multiboot.h>
#include <stdint.h>

uint32_t *memory_map = 0;
uint32_t max_blocks = 0;
uint32_t used_blocks = 0;
uint8_t phyisical_memory_ready = 0;

void init_memory_manager() {
  multiboot_info_t *boot_info = get_multiboot_info();

  multiboot_memory_map_t *memory_map =
      (multiboot_memory_map_t *)boot_info->mmap_addr;
  multiboot_memory_map_t *last_memory_map = memory_map + boot_info->mmap_length;
  uint32_t total_memory =
      last_memory_map->addr_low + last_memory_map->len_low - 1;

  init_memory_blocks(KERNEL_MALLOC, total_memory);

  for (uint32_t i = 0; i < boot_info->mmap_length;
       i += sizeof(multiboot_memory_map_t)) {
    if (memory_map->type == 1) {
      log_info("Memory map found to use at %x to %x", memory_map->addr_low,
               memory_map->len_low);
      init_memory_region(memory_map->addr_low, memory_map->len_low);
    }

    memory_map++;
  }

  // Set memory regions for the kernel as used/reserved
  lock_memory_region(0x1000, 0x9000); // Reserve memory below A000h
  lock_memory_region(KERNEL_MALLOC, max_blocks / BLOCKS_PER_BYTE);

  phyisical_memory_ready = 1;
}

void init_memory_blocks(uint32_t start_address, uint32_t size) {
  memory_map = (uint32_t *)start_address;
  max_blocks = size / BLOCK_SIZE;
  used_blocks = max_blocks; // Initialize full used

  memory_set(memory_map, 0xFF, max_blocks / BLOCKS_PER_BYTE);
}

void init_memory_region(uint32_t base_address, uint32_t size) {
  uint32_t align = base_address / BLOCK_SIZE; // Convert address to blocks
  uint32_t num_blocks = size / BLOCK_SIZE;

  for (; num_blocks > 0; num_blocks--) {
    unset_memory_block(align++);
    used_blocks--;
  }

  log_info("Memory region started using %d blocks", used_blocks);
  log_info("Memory free blocks: %d", max_blocks - used_blocks);

  set_memory_block(0);
}

void lock_memory_region(uint32_t base_address, uint32_t size) {
  uint32_t align = base_address / BLOCK_SIZE; // Convert address to blocks
  uint32_t num_blocks = size / BLOCK_SIZE;

  for (; num_blocks > 0; num_blocks--) {
    set_memory_block(align++);
    used_blocks++;
  }

  log_info("Memory used blocks: %d", used_blocks);
}

void *allocate_blocks(uint32_t num_blocks) {
  if (num_blocks == 0) {
    num_blocks = 1;
  }

  if ((max_blocks - used_blocks) < num_blocks) {
    log_info(
        "Num of blocks requested on allocation is higher than free blocks\n");
    return NULL;
  }

  int32_t start_block = find_free_blocks(num_blocks);

  if (start_block == -1) {
    log_info("No memory blocks found to be allocated\n");
    return NULL;
  }

  for (uint32_t i = 0; i < num_blocks; i++) {
    set_memory_block(start_block + i);
  }

  used_blocks += num_blocks;

  uint32_t address = start_block * BLOCK_SIZE;

  log_info("Allocating memory into %x", address);

  return (void *)address;
}

void free_blocks(uint32_t *address, uint32_t num_blocks) {
  // Rollback BLOCK_SIZE
  int32_t start_block = (uint32_t)address / BLOCK_SIZE;

  if (num_blocks == 0) {
    num_blocks = 1;
  }

  for (uint32_t i = 0; i < num_blocks; i++) {
    unset_memory_block(start_block + i);
  }

  log_info("New blocks available to use at %x", address);

  used_blocks -= num_blocks;
}

void set_memory_block(uint32_t block) {
  memory_map[block / 32] |= (1 << (block % 32));
}

void unset_memory_block(uint32_t block) {
  memory_map[block / 32] &= ~(1 << (block % 32));
}

uint8_t test_memory_block(uint32_t block) {
  return memory_map[block / 32] & (1 << (block % 32));
}

int32_t find_free_blocks(uint32_t num_blocks) {
  if (num_blocks == 0) {
    return -1;
  }

  // 32 blocks at time
  // TODO: Refactor this to better performance
  for (uint32_t i = 0; i < max_blocks / 32; i++) {
    if (memory_map[i] != 0xFFFFFFFF) {
      // Find unused bit by testing each
      for (uint32_t j = 0; j < 32; j++) {
        uint32_t bit = 1 << j;

        if (!(memory_map[i] & bit)) {
          for (uint32_t count = 0, free_blocks = 0; count <= num_blocks;
               count++) {
            if ((j + count > 31) && (i + 1 <= max_blocks / 32)) {
              if (!(memory_map[i + 1] & (1 << ((j + count) - 32)))) {
                free_blocks++;
              }
            } else {
              if (!(memory_map[i] & (1 << (j + count)))) {
                free_blocks++;
              }
            }

            if (free_blocks == num_blocks) {
              return i * 32 + j;
            }
          }
        }
      }
    }
  }

  return -1;
}
