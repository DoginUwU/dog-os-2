#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct {
  uint32_t cr2;
  uint32_t ds;
  uint32_t edi, esi, ebp, garbage, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, esp, ss;
} __attribute__((packed)) registers_t;

void irq_install_handler(int irq, void (*handler)(registers_t *r));
void irq_uninstall_handler(int irq);

void page_fault(registers_t *regs);

#endif
