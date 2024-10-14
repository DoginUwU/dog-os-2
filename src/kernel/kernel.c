#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/screen.h"

void main() {
  clear_screen();
  isr_install();

  asm volatile("sti"); // Enable Interrupts

  init_timer(50);
  init_keyboard();

  print("Welcome to DogOS\n");
  /*__asm__ __volatile__("int $2");*/
}
