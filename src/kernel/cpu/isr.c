#include <cpu/isr.h>
#include <drivers/screen.h>
#include <panic.h>
#include <ports.h>

void *irq_routines[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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

void page_fault(registers_t *regs) {
  uint32_t fault_address;
  asm volatile("mov %%cr2, %0" : "=r"(fault_address));

  int present = !(regs->err_code & 0x1);
  int rw = regs->err_code & 0x2;
  int us = regs->err_code & 0x4;
  int reserved = regs->err_code & 0x8;
  int id = regs->err_code & 0x10;

  print("Page Fault occurred without (");

  if (present) {
    print(" PRESENT ");
  }

  if (rw) {
    print(" READ-WRITE ");
  }

  if (us) {
    print(" USER-MODE ");
  }

  if (reserved) {
    print(" RESERVED ");
  }

  print(") at %x ", fault_address);
  print("ID: %d CODE: %d\n", id, regs->err_code);

  panic("Page Fault Exception!!!");
}

void isr_handler(registers_t *regs) {
  if (regs->int_no == 14) {
    page_fault(regs);
    return;
  }

  // TODO: Find out why this handle error 13 (General Protection Fault)
  if (regs->int_no < 32 && regs->int_no != 13 && regs->int_no != 6) {
    print("Exception: ");
    print(exception_messages[regs->int_no]);
    panic("ISR Exception");
  }
}

void irq_handler(registers_t *regs) {
  void (*handler)(registers_t *regs);

  handler = irq_routines[regs->int_no - 32];

  if (handler) {
    handler(regs);
  }

  if (regs->int_no >= 40) {
    port_byte_out(0xA0, 0x20);
  }

  port_byte_out(0x20, 0x20);
}

void irq_install_handler(int irq, void (*handler)(registers_t *r)) {
  irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq) { irq_routines[irq] = 0; }
