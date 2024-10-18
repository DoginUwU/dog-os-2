#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/timer.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/screen.h>
#include <lib/memory.h>

void kernel_main() {
  clear_screen();
  print("Welcome to DogOS\n");

  init_gdt();
  init_idt();

  init_timer(50);
  init_keyboard();

  /*asm volatile("int $0x3");*/
  /*asm volatile("int $0x4");*/
}
