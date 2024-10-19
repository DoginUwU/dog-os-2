#ifndef STRING_H
#define STRING_H

int string_compare(char *a, char *b);
char *string_truncate(char *str, char *delimiter);
char *string_first_ocorrence(char *str, char c);
void int_to_ascii(int num, char *str);
void append(char *str, char c);
void backspace(char *str);

#endif
