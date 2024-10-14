#ifndef MEMORY_H
#define MEMORY_H

#include "../cpu/types.h"

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(void *dest, u8 val, u32 len);

#endif
