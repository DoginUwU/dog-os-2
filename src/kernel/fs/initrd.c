#include <common.h>
#include <drivers/screen.h>
#include <fs/initrd.h>
#include <lib/cpio.h>
#include <lib/memory/memory.h>
#include <lib/string.h>
#include <stddef.h>

void process_initrd(uintptr_t initrd_start, fs_node_t *node) {
  /*uintptr_t current = initrd_start;*/
  /*cpio_header_t *header;*/
  /**/
  /*while (1) {*/
  /*  cpio_header_t *header = (cpio_header_t *)current;*/
  /**/
  /*  if (string_compare_num(header->c_magic, CPIO_MAGIC,*/
  /*                         sizeof(header->c_magic)) != 0) {*/
  /*    print("Failed to parse CPIO: Invalid magic");*/
  /*    break;*/
  /*  }*/
  /**/
  /*  uint32_t name_size =*/
  /*      hex_to_int(header->c_namesize, sizeof(header->c_namesize));*/
  /*  uint32_t file_size =*/
  /*      hex_to_int(header->c_filesize, sizeof(header->c_filesize));*/
  /**/
  /*  char *file_name = (char *)header + sizeof(cpio_header_t);*/
  /*  file_name[name_size] = '\0';*/
  /**/
  /*  if (string_compare(file_name, CPIO_TRAILER) == 0) {*/
  /*    break;*/
  /*  }*/
  /**/
  /*  uintptr_t file_data = current + sizeof(cpio_header_t) + name_size + 3;*/
  /**/
  /*  print((char *)file_data);*/
  /**/
  /*  current = file_data + file_size + 3;*/
  /*}*/
}

int mkdir_initrd(fs_node_t *node, const char *name) {
  print("oi");

  UNUSED(node);
  UNUSED(name);
  return 0;
}

fs_operations_t initrd_operations = {.mkdir = mkdir_initrd};
