#include <drivers/screen.h>
#include <lib/cpio.h>
#include <lib/string.h>

cpio_header_t *cpio_next(cpio_header_t *cpio_header) {
  uint32_t name_size =
      hex_to_int(string_substring(cpio_header->c_namesize, 0, 8));
  uint32_t file_size =
      hex_to_int(string_substring(cpio_header->c_filesize, 0, 8));

  uint32_t total_size = sizeof(cpio_header_t) + name_size + file_size;
  total_size = (total_size + 3) & ~3;

  // TODO: fix this + 4
  return (cpio_header_t *)((uint32_t)cpio_header + total_size + 4);
}
