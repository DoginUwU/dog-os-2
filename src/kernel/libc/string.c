#include "libc/string.h"
#include "memory.h"

char *int_to_hex(uint32_t num) {
  const char *hex = "0123456789ABCDEF";
  char *str = (char *)kmalloc(11);
  str[0] = '0';
  str[1] = 'x';
  str[10] = '\0';

  for (int i = 9; i > 1; i--) {
    str[i] = hex[num & 0xF];
    num >>= 4;
  }

  return str;
}
