#include <drivers/screen.h>
#include <lib/cpio.h>
#include <lib/initrd.h>
#include <lib/string.h>
#include <stddef.h>

void process_initrd(uintptr_t initrd_start) {
  cpio_header_t *cpio_header = (cpio_header_t *)initrd_start;

  while (1) {
    if (string_compare_num(cpio_header->c_magic, CPIO_MAGIC, 6) != 0) {
      break;
    }

    char *file_name = (char *)cpio_header + sizeof(cpio_header_t);
    uint32_t file_size = hex_to_int(cpio_header->c_filesize);
    print(file_name);
    print("\n");

    cpio_header = cpio_next(cpio_header);
  }
}
