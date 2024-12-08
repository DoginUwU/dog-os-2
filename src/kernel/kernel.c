#include "drivers/screen.h"
#include "memory.h"
#include "multiboot.h"

/*extern uint32_t get_kernel_stack_top();*/

int kernel_main(uint32_t checksum, uint32_t multiboot_address) {
  init_multiboot(checksum, multiboot_address);
  /*uint32_t kernel_stack_top = get_kernel_stack_top();*/
  /*println("Kernel stack top address: %x", kernel_stack_top);*/
  println("Memory regions count: %d", memory_map.count);
  for (uint32_t i = 0; i < memory_map.count; i++) {
    memory_region_t *mmap = &memory_map.regions[i];
    print("address = %x | ", mmap->addr);
    print("len = %x | ", mmap->len);
    print("type = %x", mmap->type);

    if (mmap->type == 1) {
      print(" (available)");
    } else {
      print(" (reserved)");
    }

    print("\n");

    /*if (&kernel_virtual_start >= mmap->addr &&*/
    /*    &kernel_virtual_end <= mmap->len) {*/
    /*  println("Kernel address starts in this segment ^");*/
    /*}*/
  }

  /*clear_screen();*/
  /*println("Salve salve fml");*/

  while (1) {
  }

  return 0;
}
