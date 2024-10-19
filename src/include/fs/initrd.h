#ifndef INITRD_H
#define INITRD_H

#include <fs/vfs.h>
#include <stdint.h>

void process_initrd(uintptr_t initrd_start, fs_node_t *node);

#endif
