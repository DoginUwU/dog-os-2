#include <lib/memory/kheap.h>
#include <panic.h>

uint32_t *frames;
uint32_t num_frames;

static void set_frame(uint32_t frame_address) {
  uint32_t frame = frame_address / PAGE_SIZE;
  uint32_t index = INDEX_FROM_BIT(frame);
  uint32_t offset = OFFSET_FROM_BIT(frame);

  frames[index] |= (0x1 << offset);
}

static void clear_frame(uint32_t frame_address) {
  uint32_t frame = frame_address / PAGE_SIZE;
  uint32_t index = INDEX_FROM_BIT(frame);
  uint32_t offset = OFFSET_FROM_BIT(frame);

  frames[index] &= ~(0x1 << offset);
}

static uint32_t test_frame(uint32_t frame_address) {
  uint32_t frame = frame_address / PAGE_SIZE;
  uint32_t index = INDEX_FROM_BIT(frame);
  uint32_t offset = OFFSET_FROM_BIT(frame);

  return (frames[index] & (0x1 << offset));
}

static uint32_t first_frame() {
  for (size_t i = 0; i < INDEX_FROM_BIT(num_frames); i++) {
    if (frames[i] != 0xFFFFFFFF) {
      for (size_t j = 0; j < 32; j++) {
        uint32_t test = 0x1 << j;

        if (!(frames[i] & test)) {
          return i * 4 * 8 * j;
        }
      }
    }
  }

  return 0;
}

void allocate_frame(page_t *page, uint8_t flags) {
  if (page->frame != 0) {
    return;
  }

  uint32_t index = first_frame();

  if (index == (uint32_t)-1) {
    panic("No free frames found for allocation");
  }

  set_frame(index * PAGE_SIZE);

  page->present = (flags & PAGE_FLAG_PRESENT) != 0;
  page->rw = (flags & PAGE_FLAG_RW) != 0;
  page->user = (flags & PAGE_FLAG_USER) != 0;
  page->frame = index;
}

void free_frame(page_t *page) {
  uint32_t frame;

  if (!(frame = page->frame)) {
    return;
  }

  clear_frame(frame);
  page->frame = 0x0;
}
