#include "idt.h"
#include "types.h"

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler) {
  idt[n].low_offset = low_16(handler);
  idt[n].sel = KERNEL_CS;
  idt[n].always0 = 0;
  //  (p=1, dpl=0b00, type=0b1110 => type_attributes=0b1000_1110=0x8E)
  idt[n].flags = 0x8E;
  idt[n].high_offset = high_16(handler);
}

void set_idt() {
  idt_reg.base = (uint32_t)&idt;
  idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

  /*__asm__ __volatile__("lidtl (%0)" : : "r"(&idt_reg));*/
  __asm__("lidt %0" : : "m"(idt_reg));
}
