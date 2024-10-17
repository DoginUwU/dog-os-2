#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <drivers/screen.h>

void kernel_main() {
  clear_screen();
  print("Welcome to DogOS\n");

  init_gdt();
  init_idt();

  /*asm volatile("int $0x3");*/
  /*asm volatile("int $0x4");*/
}
