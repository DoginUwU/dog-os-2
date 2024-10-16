#include <drivers/screen.h>
#include <drivers/timer.h>
#include <gdt.h>
#include <idt.h>

void kernel_main() {
  clear_screen();
  init_gdt();
  init_idt();
  /*init_irq();*/
  print("Welcome to DogOS\n");

  /*init_timer(50);*/

  asm volatile("int $0x3");
  asm volatile("int $0x4");
}
