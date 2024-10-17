#include <cpu/idt.h>
#include <lib/memory.h>
#include <ports.h>

__attribute__((aligned(0x10))) static idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

extern void idt_flush(uint32_t);

void init_idt() {
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base = (uint32_t)&idt_entries;

  memory_set(&idt_entries, 0, sizeof(idt_entry_t) * 256);

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

  set_idt_gate(0, (uint32_t)isr0, KERNEL_CS, 0x8E);
  set_idt_gate(1, (uint32_t)isr1, KERNEL_CS, 0x8E);
  set_idt_gate(2, (uint32_t)isr2, KERNEL_CS, 0x8E);
  set_idt_gate(3, (uint32_t)isr3, KERNEL_CS, 0x8E);
  set_idt_gate(4, (uint32_t)isr4, KERNEL_CS, 0x8E);
  set_idt_gate(5, (uint32_t)isr5, KERNEL_CS, 0x8E);
  set_idt_gate(6, (uint32_t)isr6, KERNEL_CS, 0x8E);
  set_idt_gate(7, (uint32_t)isr7, KERNEL_CS, 0x8E);
  set_idt_gate(8, (uint32_t)isr8, KERNEL_CS, 0x8E);
  set_idt_gate(9, (uint32_t)isr9, KERNEL_CS, 0x8E);
  set_idt_gate(10, (uint32_t)isr10, KERNEL_CS, 0x8E);
  set_idt_gate(11, (uint32_t)isr11, KERNEL_CS, 0x8E);
  set_idt_gate(12, (uint32_t)isr12, KERNEL_CS, 0x8E);
  set_idt_gate(13, (uint32_t)isr13, KERNEL_CS, 0x8E);
  set_idt_gate(14, (uint32_t)isr14, KERNEL_CS, 0x8E);
  set_idt_gate(15, (uint32_t)isr15, KERNEL_CS, 0x8E);
  set_idt_gate(16, (uint32_t)isr16, KERNEL_CS, 0x8E);
  set_idt_gate(17, (uint32_t)isr17, KERNEL_CS, 0x8E);
  set_idt_gate(18, (uint32_t)isr18, KERNEL_CS, 0x8E);
  set_idt_gate(19, (uint32_t)isr19, KERNEL_CS, 0x8E);
  set_idt_gate(20, (uint32_t)isr20, KERNEL_CS, 0x8E);
  set_idt_gate(21, (uint32_t)isr21, KERNEL_CS, 0x8E);
  set_idt_gate(22, (uint32_t)isr22, KERNEL_CS, 0x8E);
  set_idt_gate(23, (uint32_t)isr23, KERNEL_CS, 0x8E);
  set_idt_gate(24, (uint32_t)isr24, KERNEL_CS, 0x8E);
  set_idt_gate(25, (uint32_t)isr25, KERNEL_CS, 0x8E);
  set_idt_gate(26, (uint32_t)isr26, KERNEL_CS, 0x8E);
  set_idt_gate(27, (uint32_t)isr27, KERNEL_CS, 0x8E);
  set_idt_gate(28, (uint32_t)isr28, KERNEL_CS, 0x8E);
  set_idt_gate(29, (uint32_t)isr29, KERNEL_CS, 0x8E);
  set_idt_gate(30, (uint32_t)isr30, KERNEL_CS, 0x8E);
  set_idt_gate(31, (uint32_t)isr31, KERNEL_CS, 0x8E);

  set_idt_gate(128, (uint32_t)isr128, KERNEL_CS, 0x8E);
  set_idt_gate(177, (uint32_t)isr177, KERNEL_CS, 0x8E);

  idt_flush((uint32_t)&idt_ptr);
}

void set_idt_gate(uint8_t num, uint32_t base, uint16_t selector,
                  uint8_t flags) {
  idt_entries[num].base_low = base & 0xFFFF;
  idt_entries[num].base_high = (base >> 16) & 0xFFFF;

  idt_entries[num].kernel_cs = selector;
  idt_entries[num].reserved = 0;

  idt_entries[num].flags = flags | 0x60;
}
