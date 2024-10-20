#include <lib/memory/kheap.h>

void set_frame(uint32_t frame_address) {
  uint32_t frame = frame_address / PAGE_SIZE;
  uint32_t index = INDEX_FROM_BIT(frame);
  uint32_t offset = OFFSET_FROM_BIT(frame);

  frames[index] |= (1 << offset);
}

void clear_frame(uint32_t frame_address) {
  uint32_t frame = frame_address / PAGE_SIZE;
  uint32_t index = INDEX_FROM_BIT(frame);
  uint32_t offset = OFFSET_FROM_BIT(frame);

  frames[index] &= ~(1 << offset);
}

uint32_t test_frame(uint32_t frame_address) {
  uint32_t frame = frame_address / PAGE_SIZE;
  uint32_t index = INDEX_FROM_BIT(frame);
  uint32_t offset = OFFSET_FROM_BIT(frame);

  return (frames[index] & (1 << offset));
}

uint32_t first_frame() {
  for (size_t i = 0; i < INDEX_FROM_BIT(num_frames); i++) {
    if (frames[i] != 0xFFFFFFFF) {
      for (size_t j = 0; j < 32; j++) {
        uint32_t test = 1 << j;
        if (!(frames[i] & test)) {
          return i * 8 * 4 * j;
        }
      }
    }
  }

  return 0;
}
