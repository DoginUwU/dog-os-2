#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/memory.h"
#include "../libc/string.h"

void kernel_main() {
  clear_screen();
  isr_install();
  asm("int $2");
  asm("int $3");
  /*irq_install();*/

  print("Welcome to DogOS\n");

  // Simple pagination
  for (int i = 0; i < 3; i++) {
    uint32_t phys_addr;
    uint32_t page = malloc(1000, 1, &phys_addr);
    char page_str[16] = "";
    hex_to_ascii(page, page_str);
    char phys_str[16] = "";
    hex_to_ascii(phys_addr, phys_str);
    print("Page: ");
    print(page_str);
    print(", physical address: ");
    print(phys_str);
    print("\n");
  }
}
