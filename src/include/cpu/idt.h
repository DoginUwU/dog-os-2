#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define KERNEL_CS 0x08

typedef struct {
  uint16_t base_low;
  uint16_t kernel_cs;
  uint8_t reserved;
  uint8_t flags;
  uint16_t base_high;
} idt_entry_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void init_idt();
void set_idt_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void isr128(); // Sys call
extern void isr177(); // Sys call

#endif
