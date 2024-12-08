#include "drivers/screen.h"
#include "multiboot.h"

int kernel_main(uint32_t checksum, uint32_t multiboot_address) {
  init_multiboot(checksum, multiboot_address);

  /*clear_screen();*/
  /*println("Salve salve fml");*/

  while (1) {
  }

  return 0;
}
