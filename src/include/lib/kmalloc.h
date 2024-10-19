#ifndef KMALLOC_H
#define KMALLOC_H

#include <stddef.h>
#include <stdint.h>

#define INITIAL_HEAP_SIZE 0x1000
#define MAX_HEAP_SIZE 0x1000000

void *kmalloc(size_t size, int align);
void kfree(void *ptr);

#endif
