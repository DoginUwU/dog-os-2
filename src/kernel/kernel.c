#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/screen.h"

void main() {
  clear_screen();
  isr_install();

  asm volatile("sti"); // Enable Interrupts
  init_timer(50);

  print("Welcome to DogOS\n");
  /*__asm__ __volatile__("int $2");*/
}
