#include <drivers/screen.h>
#include <isr.h>
#include <ports.h>

isr_t interrupt_handlers[256];

void isr_handler(registers_t *regs) {
  print("Interrupt received: ");
  print_num(regs->int_no);
  print("\n");
}

void irq_handler(registers_t *regs) {
  if (regs->int_no >= 40) {
    port_byte_out(0xA40, 0x20); // Slave
  }

  port_byte_out(0x20, 0x20); // Master

  if (interrupt_handlers[regs->int_no] != 0) {
    isr_t handler = interrupt_handlers[regs->int_no];

    handler(regs);
  }
}

void register_interrupt_handler(uint8_t num, isr_t handler) {
  interrupt_handlers[num] = handler;
}
