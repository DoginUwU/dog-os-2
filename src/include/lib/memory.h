#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

void *memory_copy(void *dest, const void *src, size_t count);
void *memory_set(void *dest, int val, size_t count);

#endif
