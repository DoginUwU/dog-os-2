#include <lib/string.h>
#include <stddef.h>

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

void append(char *str, char c) {
  int len = str_length(str);

  str[len] = c;
  str[len + 1] = '\0';
}

void backspace(char *str) {
  int len = str_length(str);

  str[len - 1] = '\0';
}

int string_compare(char *a, char *b) {
  while (*a && *b) {
    if (*a != *b) {
      return 1;
    }

    a++;
    b++;
  }

  return *a || *b;
}

char *string_truncate(char *str, char *delimiter) {
  static char *next_token = NULL;
  char *token;

  if (str == NULL) {
    str = next_token;
  }

  if (str == NULL || *str == '\0') {
    return NULL;
  }

  while (*str && string_first_ocorrence(delimiter, *str)) {
    str++;
  }

  if (*str == '\0') {
    return NULL;
  }

  token = str;

  while (*str && !string_first_ocorrence(delimiter, *str)) {
    str++;
  }

  if (*str) {
    *str = '\0';
    next_token = str + 1;
  } else {
    next_token = str;
  }

  return token;
}

char *string_first_ocorrence(char *str, char c) {
  while (*str != '\0') {
    if (*str == c) {
      return (char *)str;
    }

    str++;
  }

  return NULL;
}
