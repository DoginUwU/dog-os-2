#include "../include/drivers/screen.h"
#include "../include/gdt.h"

void kernel_main() {
  clear_screen();
  print("Welcome to DogOS\n");
  init_gdt();
}
