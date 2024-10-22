#ifndef PHYISICAL_MEMORY_MANAGER_H
#define PHYISICAL_MEMORY_MANAGER_H

#include <stdint.h>

#define BLOCK_SIZE 0x1000 // 4kb
#define BLOCKS_PER_BYTE 8

extern uint32_t *memory_map;
extern uint32_t max_blocks;
extern uint32_t used_blocks;

void init_memory_manager();

void init_memory_blocks(uint32_t start_address, uint32_t size);
void init_memory_region(uint32_t base_address, uint32_t size);
void lock_memory_region(uint32_t base_address, uint32_t size);

uint32_t *allocate_blocks(uint32_t num_blocks);
void free_blocks(uint32_t *address, uint32_t num_blocks);

void set_memory_block(uint32_t block);
void unset_memory_block(uint32_t block);
uint8_t test_memory_block(uint32_t block);
int32_t find_free_blocks(uint32_t num_blocks);

#endif
