#include <lib/kmalloc.h>
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

int string_compare_num(char *a, char *b, int n) {
  for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      return 1;
    }
  }

  return 0;
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

uint32_t hex_to_int(const char *hex) {
  uint32_t result = 0;

  while (*hex) {
    result =
        (result << 4) | (*hex > '9' ? (*hex & ~0x20) - 'A' + 10 : (*hex - '0'));
    hex++;
  }

  return result;
}

char *string_substring(char *str, int start, int end) {
  char *substring = (char *)kmalloc(end - start + 1);

  for (int i = start; i < end; i++) {
    substring[i - start] = str[i];
  }

  substring[end - start] = '\0';

  return substring;
}

char *string_copy(char *str) {
  char *copy = (char *)kmalloc(str_length(str) + 1);

  for (int i = 0; i < str_length(str); i++) {
    copy[i] = str[i];
  }

  copy[str_length(str)] = '\0';

  return copy;
}
