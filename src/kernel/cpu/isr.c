#include <cpu/isr.h>
#include <drivers/screen.h>
#include <types.h>

__attribute__((noreturn)) void exception_handler(uint64_t isr_number);
void exception_handler(uint64_t isr_number) {
  print("Exception caught: ");
  print_num(isr_number);
  print("\n");

  __asm__ volatile("cli; hlt"); // For now hangs the computer
}
