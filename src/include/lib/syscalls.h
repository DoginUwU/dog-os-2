#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

void enter_user_mode(const uint32_t user_stack, const uint32_t user_code);

#endif
