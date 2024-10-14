#ifndef IDT_H
#define IDT_H

#include "types.h"

// Kernel Code Segment
#define KERNEL_CS 0x08

typedef struct {
  u16 low_offset; // Lower 16 bits of address to jump when interrupt
  u16 sel;        // Kernel segment selector
  u8 always0;     // Needs to be 0

  u8 flags;        // type_attributes in
                   // https://wiki.osdev.org/Interrupt_Descriptor_Table
  u16 high_offset; // Higher 16 bits of address
} __attribute__((packed)) idt_gate_t;

typedef struct {
  u16 limit;
  u32 base; // Address of first elemenent in idt_gate_t; LIDT will read it
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256 // less than that causes cpu segmentation fault
extern idt_gate_t idt[IDT_ENTRIES];
extern idt_register_t idt_reg;

void set_idt_gate(int n, u32 handler);
void set_idt();

#endif
