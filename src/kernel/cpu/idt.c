#include <cpu/idt.h>

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags);
void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags) {
  idt_entry_t *idt_entry = &idt_entries[vector];

  idt_entry->isr_low = (uint64_t)isr & 0xFFFF;
  idt_entry->kernel_cs = KERNEL_CS;
  idt_entry->ist = 0;
  idt_entry->attributes = flags;
  idt_entry->isr_mid = ((uint64_t)isr >> 16) & 0xFFFF;
  idt_entry->isr_hight = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
  idt_entry->reserved = 0;
}

void init_idt() {
  idt_ptr.base = (uint64_t)&idt_entries;
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;

  idt_set_descriptor(0, isr0, 0x8E);
  idt_set_descriptor(1, isr1, 0x8E);
  idt_set_descriptor(2, isr2, 0x8E);
  idt_set_descriptor(3, isr3, 0x8E);
  idt_set_descriptor(4, isr4, 0x8E);
  idt_set_descriptor(5, isr5, 0x8E);
  idt_set_descriptor(6, isr6, 0x8E);
  idt_set_descriptor(7, isr7, 0x8E);
  idt_set_descriptor(8, isr8, 0x8E);
  idt_set_descriptor(9, isr9, 0x8E);
  idt_set_descriptor(10, isr10, 0x8E);
  idt_set_descriptor(11, isr11, 0x8E);
  idt_set_descriptor(12, isr12, 0x8E);
  idt_set_descriptor(13, isr13, 0x8E);
  idt_set_descriptor(14, isr14, 0x8E);
  idt_set_descriptor(15, isr15, 0x8E);
  idt_set_descriptor(16, isr16, 0x8E);
  idt_set_descriptor(17, isr17, 0x8E);
  idt_set_descriptor(18, isr18, 0x8E);
  idt_set_descriptor(19, isr19, 0x8E);
  idt_set_descriptor(20, isr20, 0x8E);
  idt_set_descriptor(21, isr21, 0x8E);
  idt_set_descriptor(22, isr22, 0x8E);
  idt_set_descriptor(23, isr23, 0x8E);
  idt_set_descriptor(24, isr24, 0x8E);
  idt_set_descriptor(25, isr25, 0x8E);
  idt_set_descriptor(26, isr26, 0x8E);
  idt_set_descriptor(27, isr27, 0x8E);
  idt_set_descriptor(28, isr28, 0x8E);
  idt_set_descriptor(29, isr29, 0x8E);
  idt_set_descriptor(30, isr30, 0x8E);
  idt_set_descriptor(31, isr31, 0x8E);

  __asm__ volatile("lidt %0" : : "m"(idt_ptr));
  __asm__ volatile("sti");
}
