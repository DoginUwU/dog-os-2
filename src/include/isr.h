#ifndef ISR_H
#define ISR_H

#include "types.h"

typedef struct registers {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, code_err;
  uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

void isr_handler(registers_t regs);

#endif
