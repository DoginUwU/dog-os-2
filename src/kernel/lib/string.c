#include "../../include/lib/string.h"

void reverse(char *str);
int str_length(char *str);

void int_to_ascii(int num, char *str) {
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
}

void reverse(char *str) {
  int c, i, j;

  for (i = 0, j = str_length(str) - 1; i < j; i++, j--) {
    c = str[i];
    str[i] = str[j];
    str[j] = c;
  }
}

int str_length(char *str) {
  int i = 0;

  while (str[i] != '\0') {
    i++;
  }

  return i;
}
