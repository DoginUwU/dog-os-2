#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/screen.h"

void main() {
  clear_screen();
  isr_install();
  irq_install();

  print("Welcome to DogOS\n");
}
