#ifndef STRING_H
#define STRING_H

#include <stdint.h>

int string_compare(const char *a, const char *b);
int string_compare_num(const char *a, const char *b, int n);
char *string_truncate(char *str, char *delimiter);
char *string_first_ocorrence(char *str, char c);
char *string_substring(const char *str, int start, int end);
char *string_copy(const char *str);
void int_to_ascii(int num, char *str);
uint32_t hex_to_int(const char *hex);
char *int_to_hex(uint32_t n);
void append(char *str, char c);
void backspace(char *str);

#endif
