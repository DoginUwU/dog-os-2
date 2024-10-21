#ifndef STRING_H
#define STRING_H

#include <stdint.h>

int string_compare(const char *a, const char *b);
int string_compare_num(const char *a, const char *b, int n);
char *string_truncate(char *str, char *delimiter);
char *string_first_ocorrence(char *str, char c);
char *string_substring(const char *str, int start, int end);
char *string_copy(const char *str);
char *string_concat(const char *a, const char *b);
void int_to_ascii(int num, char *str);
uint32_t hex_to_int(const char *hex, uint32_t max_size);
char *int_to_hex(uint32_t n);
void append(char *str, char c);
void backspace(char *str);
int string_length(const char *str);

#endif
