#include <drivers/screen.h>
#include <lib/cpio.h>
#include <lib/string.h>

cpio_header_t *cpio_next(cpio_header_t *cpio_header) {
  uint32_t namesize =
      hex_to_int(string_substring(cpio_header->c_namesize, 0, 8));
  uint32_t filesize =
      hex_to_int(string_substring(cpio_header->c_filesize, 0, 8));

  uint32_t total_size = sizeof(cpio_header_t) + namesize + filesize;
  total_size = (total_size + 3) & ~3;

  return (cpio_header_t *)((uint32_t)cpio_header + total_size);
}
