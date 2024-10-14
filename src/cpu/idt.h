#ifndef IDT_H
#define IDT_H

#include "types.h"
#include <stdint.h>

// Kernel Code Segment
#define KERNEL_CS 0x08

typedef struct {
  uint16_t low_offset; // Lower 16 bits of address to jump when interrupt
  uint16_t sel;        // Kernel segment selector
  uint8_t always0;     // Needs to be 0

  uint8_t flags;        // type_attributes in
                        // https://wiki.osdev.org/Interrupt_Descriptor_Table
  uint16_t high_offset; // Higher 16 bits of address
} __attribute__((packed)) idt_gate_t;

typedef struct {
  uint16_t limit;
  uint32_t base; // Address of first elemenent in idt_gate_t; LIDT will read it
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256 // less than that causes cpu segmentation fault
extern idt_gate_t idt[IDT_ENTRIES];
extern idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif
