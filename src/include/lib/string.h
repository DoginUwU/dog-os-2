#ifndef STRING_H
#define STRING_H

#include <stdint.h>

int string_compare(char *a, char *b);
int string_compare_num(char *a, char *b, int n);
char *string_truncate(char *str, char *delimiter);
char *string_first_ocorrence(char *str, char c);
char *string_substring(char *str, int start, int end);
void int_to_ascii(int num, char *str);
uint32_t hex_to_int(const char *hex);
void append(char *str, char c);
void backspace(char *str);

#endif
