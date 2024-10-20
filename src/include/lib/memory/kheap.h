#ifndef KHEAP_H
#define KHEAP_H

#include <lib/memory/memory.h>
#include <stdint.h>

#define INDEX_FROM_BIT(a) (a / (8 * 4))
#define OFFSET_FROM_BIT(a) (a % (8 * 4))

extern uint32_t placement_address;

uint32_t *frames;
uint32_t num_frames;

void set_frame(uint32_t frame_address);
void clear_frame(uint32_t frame_address);
uint32_t test_frame(uint32_t frame_address);
uint32_t first_frame();

/*void allocate_frame(page_t *page, uint8_t flags);*/
/*void free_frame(page_t *page);*/

#endif
