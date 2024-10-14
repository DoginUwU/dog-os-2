#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/memory.h"
#include "../libc/string.h"

void main() {
  clear_screen();
  isr_install();
  irq_install();

  print("Welcome to DogOS\n");

  // Simple pagination
  for (int i = 0; i < 3; i++) {
    u32 phys_addr;
    u32 page = malloc(1000, 1, &phys_addr);
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
