#include "multiboot.h"
#include "drivers/screen.h"

void init_multiboot(uint32_t checksum, uint32_t multiboot_address) {
  if (checksum != MULTIBOOT2_CHECKSUM) {
    println("Invalid multiboot2 checksum");
  }

  if (multiboot_address & 7) {
    println("Unaligned multiboot header");
  }

  multiboot_tag_t *tag;

  for (tag = (multiboot_tag_t *)(multiboot_address + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (multiboot_tag_t *)((uint8_t *)tag + ((tag->size + 7) & ~7))) {
    switch (tag->type) {
    case MULTIBOOT_TAG_TYPE_MMAP:
      multiboot_memory_map_t *mmap;

      for (mmap = ((multiboot_tag_mmap_t *)tag)->entries;
           (uint8_t *)mmap < (uint8_t *)tag + tag->size;
           mmap = (multiboot_memory_map_t *)((unsigned long)mmap +
                                             ((multiboot_tag_mmap_t *)tag)
                                                 ->entry_size)) {
        print("address = %x | ", mmap->addr);
        print("len = %x | ", mmap->len);
        print("type = %x\n", mmap->type);
      }
      break;
    }
  }
}
