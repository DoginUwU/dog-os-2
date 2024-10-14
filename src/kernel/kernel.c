#include "../cpu/isr.h"
#include "../drivers/screen.h"

void main() {
  isr_install();

  clear_screen();

  print("Welcome to DogOS\n");
}
