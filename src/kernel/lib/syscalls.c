#include <lib/logging.h>
#include <lib/syscalls.h>

void enter_user_mode(const uint32_t user_stack, const uint32_t user_code) {
  asm volatile("cli;"

               "mov $0x23, %%ax;" // 0x23 is the segment of user data
               "mov %%ax, %%ds;"
               "mov %%ax, %%es;"
               "mov %%ax, %%fs;"
               "mov %%ax, %%gs;"

               "pushl $0x23;"
               "pushl %0;"
               "pushfl;"
               "popl %%eax;"
               "orl $0x200, %%eax;"
               "pushl %%eax;"
               "pushl $0x1B;"
               "pushl %1;"

               "iret;"
               :
               : "r"(user_stack), "r"(user_code)
               : "eax");

  log_info("User-mode enabled");
}
