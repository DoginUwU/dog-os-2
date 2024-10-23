#include <lib/logging.h>
#include <lib/syscalls.h>

void enter_user_mode() {
  asm volatile("  \
     cli; \
     mov $0x23, %ax; \
     mov %ax, %ds; \
     mov %ax, %es; \
     mov %ax, %fs; \
     mov %ax, %gs; \
                   \
     mov %esp, %eax; \
     pushl $0x23; \
     pushl %eax; \
     pushf; \
		 pop %eax; \
		 orl $0x200, %eax; \
		 push %eax; \
     pushl $0x1B; \
     push $1f; \
     iret; \
   1: \
     ");

  log_info("User-mode enabled");
}
