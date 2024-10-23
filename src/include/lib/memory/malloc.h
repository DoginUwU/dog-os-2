#ifndef KMALLOC_H
#define KMALLOC_H

#include <stddef.h>
#include <stdint.h>

void *malloc(const size_t size);
void free(const void *ptr);

void *kmalloc(size_t size);
void *kmalloc_align(size_t size);
void *kmalloc_align_pysical(size_t size, uint32_t *physical_address);

#endif
