#include <lib/logging.h>
#include <lib/syscalls.h>

extern void jump_usermode();

void enter_user_mode() { jump_usermode(); }
