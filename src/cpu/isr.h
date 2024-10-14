#ifndef ISR_H
#define ISR_H

#include "types.h"

// ISRs for CPU exceptions
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

// IRQs
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#define IRQ_COUNTER 32  // Invertal counter
#define IRQ_KEYBOARD 33 // Keyboard
#define IRQ2 34         // 8259B
#define IRQ3 35         // COM2 & COM4
#define IRQ4 36         // COM1 & COM3
#define IRQ5 37         // LPT2 & Sound Card
#define IRQ6 38         // Floppy
#define IRQ7 39         // LPT1
#define IRQ8 40         // Real Time Clock (RTC)
#define IRQ9 41         // IRQ2
#define IRQ10 42        // Unknown
#define IRQ11 43        // Unknown
#define IRQ12 44        // Mouse PS/2
#define IRQ13 45        // Coprocessor
#define IRQ14 46        // Primary IDE
#define IRQ15 47        // Secondary IDE

typedef struct {
  u32 ds;                                     // Data segment selector
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pusha
  u32 int_no, erro_code;                      // Interrupt number and error code
  u32 eip, cs, eflags, useresp, ss;           // By cpu
} registers_t;

void isr_install();
void isr_handler(registers_t r);

void irq_install();
void irq_handler(registers_t r);

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(u8 n, isr_t handler);

#endif
