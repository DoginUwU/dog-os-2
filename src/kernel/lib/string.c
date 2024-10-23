#include <lib/memory/malloc.h>
#include <lib/memory/phyisical_memory_manager.h>
#include <lib/string.h>
#include <stddef.h>

void reverse(char *str);

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

void append(char *str, const char c) {
  int len = string_length(str);

  str[len] = c;
  str[len + 1] = '\0';
}

void backspace(char *str) {
  int len = string_length(str);

  str[len - 1] = '\0';
}

int string_compare(const char *a, const char *b) {
  while (*a && *b) {
    if (*a != *b) {
      return 1;
    }

    a++;
    b++;
  }

  return *a || *b;
}

int string_compare_num(const char *a, const char *b, int n) {
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

uint32_t hex_to_int(const char *hex, uint32_t max_size) {
  uint32_t result = 0;

  for (uint32_t i = 0; i < max_size; i++) {
    result *= 16;

    if (hex[i] >= '0' && hex[i] <= '9') {
      result += hex[i] - '0';
    } else if (hex[i] >= 'a' && hex[i] <= 'f') {
      result += hex[i] - 'a' + 10;
    } else if (hex[i] >= 'A' && hex[i] <= 'F') {
      result += hex[i] - 'A' + 10;
    } else {
      return result;
    }
  }

  return result;
}

char *string_substring(const char *str, int start, int end) {
  char *substring = (char *)kmalloc(end - start + 1);

  for (int i = start; i < end; i++) {
    substring[i - start] = str[i];
  }

  substring[end - start] = '\0';

  return substring;
}

char *string_copy(const char *str) {
  char *copy = (char *)kmalloc(string_length(str) + 1);

  for (int i = 0; i < string_length(str); i++) {
    copy[i] = str[i];
  }

  copy[string_length(str)] = '\0';

  return copy;
}

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

char *int_to_hex_64(uint64_t n) {
  const char *hex = "0123456789ABCDEF";
  char *str = (char *)kmalloc(17);
  str[0] = '0';
  str[1] = 'x';
  str[16] = '\0';

  for (int i = 15; i > 1; i--) {
    str[i] = hex[n & 0xF];
    n >>= 4;
  }

  return str;
}

char *string_concat(const char *a, const char *b) {
  char *concat = (char *)kmalloc(string_length(a) + string_length(b) + 1);

  if (concat == NULL) {
    return NULL;
  }

  int i = 0;

  for (int j = 0; j < string_length(a); j++) {
    concat[i++] = a[j];
  }

  for (int j = 0; j < string_length(b); j++) {
    concat[i++] = b[j];
  }

  concat[i] = '\0';

  return concat;
}
