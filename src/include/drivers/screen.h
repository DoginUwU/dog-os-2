#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xC00B8000

#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x07
#define RED_ON_WHITE 0xF4

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#define EMPTY_CHAR 0x08

void print(char *message);
void print_num(int num);
void print_at(char *message, int col, int row);
void print_backspace();
void clear_screen();

#endif
