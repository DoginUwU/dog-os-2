#include "../../include/drivers/screen.h"
#include "../../include/lib/memory.h"
#include "../../include/lib/string.h"
#include "../../include/ports.h"
#include "../../include/types.h"

int print_char(char c, int col, int row, char attr);

int get_cursor_offset();
void set_cursor_offset(int offset);

int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void print_at(char *message, int col, int row) {
  int offset = 0;

  if (col >= 0 || row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();

    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  int i = 0;

  while (message[i] != 0) {
    offset = print_char(message[i++], col, row, WHITE_ON_BLACK);

    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void print(char *message) { print_at(message, -1, -1); }
void print_num(int num) {
  char *str[3];
  int_to_ascii(num, str);
  print(str);
}

int print_char(char c, int col, int row, char attr) {
  uint8_t *video_memory = (uint8_t *)VIDEO_ADDRESS;

  if (!attr) {
    attr = WHITE_ON_BLACK;
  }

  if (col >= MAX_COLS || row > +MAX_ROWS) {
    video_memory[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
    video_memory[2 * (MAX_COLS) * (MAX_ROWS)-1] = RED_ON_WHITE;

    return get_offset(col, row);
  }

  int offset = 0;

  if (col >= 0 || row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
  }

  if (c == '\n') {
    row = get_offset_row(offset);
    offset = get_offset(0, row + 1);
  } else if (c == EMPTY_CHAR) {
    video_memory[offset] = ' ';
    video_memory[offset + 1] = attr;
  } else {
    video_memory[offset] = c;
    video_memory[offset + 1] = attr;

    offset += 2;
  }

  if (offset >= MAX_ROWS * MAX_COLS * 2) {
    for (int i = 0; i < MAX_ROWS; i++) {
      memcpy((char *)get_offset(0, i) + VIDEO_ADDRESS,
             (char *)get_offset(0, i - 1) + VIDEO_ADDRESS, MAX_COLS * 2);
    }

    char *last_line = (char *)get_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;

    for (int i = 0; i < MAX_COLS * 2; i++) {
      last_line[i] = 0;
    }

    offset -= 2 * MAX_COLS;
  }

  set_cursor_offset(offset);

  return offset;
}

void print_backspace() {
  int offset = get_cursor_offset() - 2;

  int row = get_offset_row(offset);
  int col = get_offset_col(offset);

  print_char(EMPTY_CHAR, col, row, WHITE_ON_BLACK);
}

void clear_screen() {
  int screen_size = MAX_COLS * MAX_ROWS;
  uint8_t *video_memory = (uint8_t *)VIDEO_ADDRESS;

  for (int i = 0; i < screen_size; i++) {
    video_memory[i * 2] = ' ';
    video_memory[i * 2 + 1] = WHITE_ON_BLACK;
  }

  set_cursor_offset(get_offset(0, 0));
}

int get_cursor_offset() {
  int offset = 0;

  port_byte_out(REG_SCREEN_CTRL, 14);
  offset += port_byte_in(REG_SCREEN_DATA) << 8;

  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);

  return offset * 2;
}

void set_cursor_offset(int offset) {
  offset /= 2;

  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, high_8(offset));

  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, low_8(offset));
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) {
  return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}
