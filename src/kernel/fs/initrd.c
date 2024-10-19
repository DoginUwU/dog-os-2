#include <drivers/screen.h>
#include <fs/initrd.h>
#include <lib/cpio.h>
#include <lib/string.h>
#include <stddef.h>

void process_initrd(uintptr_t initrd_start, fs_node_t *node) {
  cpio_header_t *cpio_header = (cpio_header_t *)initrd_start;

  while (1) {
    if (string_compare_num(cpio_header->c_magic, CPIO_MAGIC, 6) != 0) {
      break;
    }

    char *file_name = (char *)cpio_header + sizeof(cpio_header_t);

    vfs_create_file(file_name, 0, 0, node);

    cpio_header = cpio_next(cpio_header);
  }
}

int mkdir_initrd(fs_node_t *node, const char *name) {
  print("oi");
  return 0;
}

fs_operations_t initrd_operations = {.mkdir = mkdir_initrd};
