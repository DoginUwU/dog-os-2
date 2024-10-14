#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(void *dest, uint8_t val, uint32_t len);
uint32_t malloc(uint32_t size, int align, uint32_t *addr);

#endif
