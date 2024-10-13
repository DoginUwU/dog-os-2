#include "screen.h"
#include "ports.h"

int get_cursor_offset();
void set_cursor_offset(int offset);

int print_char(char c, int col, int row, char attr);

int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void print_at(char *message, int col, int row) {
  int offset;

  if (col >= 0 && row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  int i = 0;

  while (message[i] != 0) {
    offset = print_char(message[i++], col, row, WHITE_ON_BLACK);

    /* Compute next row/col from next interation */
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void print(char *message) { print_at(message, -1, -1); }

int print_char(char c, int col, int row, char attr) {
  unsigned char *video_memory = (unsigned char *)VIDEO_ADDRESS;

  if (!attr) {
    attr = WHITE_ON_BLACK;
  }

  /* If has error in control, print some flag alert */
  if (col >= MAX_COLS || row >= MAX_ROWS) {
    video_memory[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
    video_memory[2 * (MAX_COLS) * (MAX_ROWS)-1] = RED_ON_WHITE;

    return get_offset(col, row);
  }

  int offset;

  if (col >= 0 && row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
  }

  /* Break line if need */
  if (c == '\n') {
    row = get_offset_row(offset);
    offset = get_offset(0, row + 1);
  } else {
    video_memory[offset] = c;
    video_memory[offset + 1] = attr;

    offset += 2;
  }

  set_cursor_offset(offset);

  return offset;
}

int get_cursor_offset() {
  /* https://wiki.osdev.org/VGA_Hardware#Port_0x3C4,_0x3CE,_0x3D4 */
  /* Get cursor pos from VGA port */
  /*	- from high byte from the cursor offset (data 14) */
  /*	- from low byte from the cursor offset (data 15) */

  int offset;

  port_byte_out(REG_SCREEN_CTRL, 14);
  offset += port_byte_in(REG_SCREEN_DATA) << 8;

  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);

  return offset * 2;
}

void set_cursor_offset(int offset) {
  // Convert byte pos to character (2)
  offset /= 2;

  port_byte_out(REG_SCREEN_CTRL, 14); // Access high byte
  port_byte_out(REG_SCREEN_DATA,
                (unsigned char)(offset >> 8)); // Send the 8 high bits

  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
  int screen_size = MAX_COLS * MAX_ROWS;
  unsigned char *screen = (unsigned char *)VIDEO_ADDRESS;

  int i;

  for (i = 0; i < screen_size; i++) {
    screen[i * 2] = ' ';
    screen[i * 2 + 1] = WHITE_ON_BLACK;
  }

  set_cursor_offset(get_offset(0, 0));
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) {
  return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}
