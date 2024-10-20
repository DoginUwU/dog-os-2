#include <common.h>
#include <drivers/screen.h>
#include <fs/initrd.h>
#include <lib/cpio.h>
#include <lib/memory/memory.h>
#include <lib/string.h>
#include <stddef.h>

void process_initrd(uintptr_t initrd_start, fs_node_t *node) {
  print((char *)initrd_start);
}

int mkdir_initrd(fs_node_t *node, const char *name) {
  UNUSED(node);
  UNUSED(name);
  return 0;
}

fs_operations_t initrd_operations = {.mkdir = mkdir_initrd};
