#include "multiboot.h"
#include "drivers/screen.h"
#include "memory.h"

/*extern uint32_t kernel_virtual_start;*/
/*extern uint32_t kernel_virtual_end;*/

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

      /*uint32_t available_memory_len = 0;*/

      memory_map.count = tag->size / ((multiboot_tag_mmap_t *)tag)->entry_size;
      memory_map.regions = kmalloc(memory_map.count * sizeof(memory_region_t));

      uint32_t index = 0;
      for (mmap = ((multiboot_tag_mmap_t *)tag)->entries;
           (uint8_t *)mmap < (uint8_t *)tag + tag->size;
           mmap = (multiboot_memory_map_t *)((unsigned long)mmap +
                                             ((multiboot_tag_mmap_t *)tag)
                                                 ->entry_size)) {
        memory_map.regions[index].addr = mmap->addr;
        memory_map.regions[index].len = mmap->len;

        if (mmap->type == 1) {
          memory_map.regions[index].type = MEMORY_REGION_AVAILABLE;
        } else {
          memory_map.regions[index].type = MEMORY_REGION_RESERVED;
        }

        index++;

        /*print("address = %x | ", mmap->addr);*/
        /*print("len = %x | ", mmap->len);*/
        /*print("type = %x", mmap->type);*/
        /**/
        /*if (mmap->type == 1) {*/
        /*  print(" (available)");*/
        /*} else {*/
        /*  print(" (reserved)");*/
        /*}*/
        /**/
        /*print("\n");*/
        /**/
        /*if (&kernel_virtual_start >= mmap->addr &&*/
        /*    &kernel_virtual_end <= mmap->len) {*/
        /*  println("Kernel address starts in this segment ^");*/
        /*}*/
        /**/
        /*available_memory_len += mmap->len;*/
        /*memory_map.count++;*/
      }

      /*println("\nMemory available in system: %dMB",*/
      /*        available_memory_len / 1024 / 1024);*/
      break;
    }
  }
}
