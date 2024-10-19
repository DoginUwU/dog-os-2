#ifndef KHEAP_H
#define KHEAP_H

#include <lib/memory/memory.h>
#include <stdint.h>

extern uint32_t placement_address;

#define INDEX_FROM_BIT(a) (a / (8 * 4))
#define OFFSET_FROM_BIT(a) (a % (8 * 4))

static void set_frame(uint32_t frame_address);
static void clear_frame(uint32_t frame_address);
static uint32_t test_frame(uint32_t frame_address);
static uint32_t first_frame();

void allocate_frame(page_t *page, uint8_t flags);
void free_frame(page_t *page);

#endif
