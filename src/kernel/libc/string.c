#include "libc/string.h"
#include "memory/memory.h"

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

char *int_to_char(uint32_t num) {
  char *str = (char *)kmalloc(11);
  int i, sign;

  if ((sign = num) < 0)
    num = -num;

  i = 0;

  do {
    str[i++] = num % 10 + '0';
  } while ((num /= 10) > 0);

  if (sign < 0)
    str[i++] = '-';

  str[i] = '\0';

  reverse(str);

  return str;
}

void reverse(char *str) {
  int c, i, j;

  for (i = 0, j = string_length(str) - 1; i < j; i++, j--) {
    c = str[i];
    str[i] = str[j];
    str[j] = c;
  }
}

int string_length(const char *str) {
  int i = 0;

  while (str[i] != '\0') {
    i++;
  }

  return i;
}
