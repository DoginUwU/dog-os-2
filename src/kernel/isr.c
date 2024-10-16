#include "../include/isr.h"
#include "../include/drivers/screen.h"

void isr_handler(registers_t regs) {
  print("Interrupt received: ");
  print_num(regs.int_no);
  print("\n");
}
