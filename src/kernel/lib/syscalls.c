#include <cpu/gdt.h>
#include <lib/logging.h>
#include <lib/syscalls.h>

extern uint32_t _user_stack_end;
extern uint32_t _user_code_start;
extern uint32_t _kernel_stack_end;
extern tss_entry_t tss_entry;

void switch_to_user_mode() {
  tss_entry.ss0 = 0x10;
  tss_entry.esp0 = (uint32_t)&_kernel_stack_end;

  uint32_t user_stack = (uint32_t)&_user_stack_end;
  uint32_t user_code = (uint32_t)&_user_code_start;

  asm volatile("cli;"
               "mov $0x23, %%ax;"
               "mov %%ax, %%ds;"
               "mov %%ax, %%es;"
               "mov %%ax, %%fs;"
               "mov %%ax, %%gs;"

               "mov %0, %%eax;"
               "push $0x23;"
               "push %%eax;"
               "pushf;"

               "pop %%eax;"
               "or $0x200, %%eax;"
               "push %%eax;"

               "push $0x1B;"
               "push %1;"
               "iret;"
               :
               : "r"(user_stack), "r"(user_code)
               : "eax");
}
