#ifndef MEMORY_H
#define MEMORY_H

#include "../cpu/types.h"

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(void *dest, uint8_t val, uint32_t len);
uint32_t malloc(size_t size, int align, uint32_t *addr);

#endif
