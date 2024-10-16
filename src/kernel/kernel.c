#include <drivers/screen.h>
#include <gdt.h>
#include <idt.h>

void kernel_main() {
  clear_screen();
  init_gdt();
  init_idt();
  print("Welcome to DogOS\n");

  /*asm volatile("int $0x3");*/
  /*asm volatile("int $0x4");*/
}
