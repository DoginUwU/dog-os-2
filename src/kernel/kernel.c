#include <cpu/gdt.h>
#include <drivers/screen.h>

void kernel_main() {
  clear_screen();
  print("Welcome to DogOS\n");

  init_gdt();
}
