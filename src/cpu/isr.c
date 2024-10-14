#include "isr.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "idt.h"
#include "ports.h"
#include "timer.h"
#include <stdint.h>

isr_t interrupt_handlers[256];

void isr_install() {
  set_idt_gate(0, (uint32_t)isr0);
  set_idt_gate(1, (uint32_t)isr1);
  set_idt_gate(2, (uint32_t)isr2);
  set_idt_gate(3, (uint32_t)isr3);
  set_idt_gate(4, (uint32_t)isr4);
  set_idt_gate(5, (uint32_t)isr5);
  set_idt_gate(6, (uint32_t)isr6);
  set_idt_gate(7, (uint32_t)isr7);
  set_idt_gate(8, (uint32_t)isr8);
  set_idt_gate(9, (uint32_t)isr9);
  set_idt_gate(10, (uint32_t)isr10);
  set_idt_gate(11, (uint32_t)isr11);
  set_idt_gate(12, (uint32_t)isr12);
  set_idt_gate(13, (uint32_t)isr13);
  set_idt_gate(14, (uint32_t)isr14);
  set_idt_gate(15, (uint32_t)isr15);
  set_idt_gate(16, (uint32_t)isr16);
  set_idt_gate(17, (uint32_t)isr17);
  set_idt_gate(18, (uint32_t)isr18);
  set_idt_gate(19, (uint32_t)isr19);
  set_idt_gate(20, (uint32_t)isr20);
  set_idt_gate(21, (uint32_t)isr21);
  set_idt_gate(22, (uint32_t)isr22);
  set_idt_gate(23, (uint32_t)isr23);
  set_idt_gate(24, (uint32_t)isr24);
  set_idt_gate(25, (uint32_t)isr25);
  set_idt_gate(26, (uint32_t)isr26);
  set_idt_gate(27, (uint32_t)isr27);
  set_idt_gate(28, (uint32_t)isr28);
  set_idt_gate(29, (uint32_t)isr29);
  set_idt_gate(30, (uint32_t)isr30);
  set_idt_gate(31, (uint32_t)isr31);

  // Remap PIC
  port_byte_out(0x20, 0x11);
  port_byte_out(0xA0, 0x11);
  port_byte_out(0x21, 0x20);
  port_byte_out(0xA1, 0x28);
  port_byte_out(0x21, 0x04);
  port_byte_out(0xA1, 0x02);
  port_byte_out(0x21, 0x01);
  port_byte_out(0xA1, 0x01);
  port_byte_out(0x21, 0x0);
  port_byte_out(0xA1, 0x0);

  // Install IRQs
  set_idt_gate(IRQ_COUNTER, (uint32_t)irq0);
  set_idt_gate(IRQ_KEYBOARD, (uint32_t)irq1);
  set_idt_gate(IRQ2, (uint32_t)irq2);
  set_idt_gate(IRQ3, (uint32_t)irq3);
  set_idt_gate(IRQ4, (uint32_t)irq4);
  set_idt_gate(IRQ5, (uint32_t)irq5);
  set_idt_gate(IRQ6, (uint32_t)irq6);
  set_idt_gate(IRQ7, (uint32_t)irq7);
  set_idt_gate(IRQ8, (uint32_t)irq8);
  set_idt_gate(IRQ9, (uint32_t)irq9);
  set_idt_gate(IRQ10, (uint32_t)irq10);
  set_idt_gate(IRQ11, (uint32_t)irq11);
  set_idt_gate(IRQ12, (uint32_t)irq12);
  set_idt_gate(IRQ13, (uint32_t)irq13);
  set_idt_gate(IRQ14, (uint32_t)irq14);
  set_idt_gate(IRQ15, (uint32_t)irq15);

  set_idt();
}

// https://wiki.osdev.org/Interrupt_Vector_Table
char *exception_messages[] = {
    "Divide by 0",
    "Reserved",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Out of Bounds",
    "Invalid opcode",
    "Device not available",

    "Double fault",
    "Coprocessor segment overrun",
    "Invalid TTS",
    "Segment not present",
    "Stack-segment fault",
    "General protection fault",
    "Page fault",
    "Reserved",

    "x87 FPU error",
    "Alignment check",
    "Machine check",
    "SIMD Floating-Point Exception",
    "Reserved",
    "User definable",

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

void isr_handler(registers_t r) {
  print("[ERROR] CPU interrupt: ");

  char s[3];

  int_to_ascii(r.int_no, s);
  print(s);
  print("\n");
  print(exception_messages[r.int_no]);
  print("\n");
}

void irq_install() {
  asm volatile("sti");

  init_timer(50);
  init_keyboard();
}

void irq_handler(registers_t r) {
  if (r.int_no >= 40)
    port_byte_out(0xA0, 0x20); // Slave

  port_byte_out(0x20, 0x20);

  if (interrupt_handlers[r.int_no] != 0) {
    isr_t handler = interrupt_handlers[r.int_no];

    handler(r);
  }
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}
