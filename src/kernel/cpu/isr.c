#include <cpu/isr.h>
#include <drivers/screen.h>

char *exception_messages[] = {
    "Divide by Zero",
    "Debug",
    "Non Maskable Interrupt NMI",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Fault",
    "Machine Check",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

void isr_handler(registers_t *regs) {
  // TODO: Find out why this handle error 13 (General Protection Fault)
  if (regs->int_no < 32 && regs->int_no != 13) {
    print("Exception: ");
    print(exception_messages[regs->int_no]);
    print("\n");

    while (1) {
    }
  }
}
