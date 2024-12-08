#include "drivers/screen.h"
#include "libc/string.h"
#include "ports.h"
#include <stdarg.h>

vga_color_entry_t current_terminal_color = {.fg = VGA_COLOR_GRAY,
                                            .bg = VGA_COLOR_BLACK};

uint16_t get_offset(const uint8_t x, const uint8_t y);
uint16_t get_offset_x(const uint16_t offset);
uint16_t get_offset_y(const uint16_t offset);
uint16_t get_cursor_offset();

void set_cursor_offset(const uint16_t offset);

void print_at(const char *format, int8_t x, int8_t y, va_list args);

void println(const char *format, ...) {
  va_list args;
  va_start(args, format);
  va_list args_copy;
  va_copy(args_copy, args);

  print_at(format, -1, -1, args_copy);
  print_at("\n", -1, -1, args_copy);

  va_end(args);
}

void print(const char *format, ...) {
  va_list args;
  va_start(args, format);
  va_list args_copy;
  va_copy(args_copy, args);

  print_at(format, -1, -1, args_copy);

  va_end(args);
}

void print_hex_32(uint32_t hex) {
  char *data = int_to_hex(hex);
  print(data);
}

void print_num(uint32_t num) {
  char *data = int_to_char(num);
  print(data);
}

void print_at(const char *format, int8_t x, int8_t y, va_list args) {
  uint16_t index = 0;
  uint16_t offset = 0;

  if (x < 0 || y < 0) {
    offset = get_cursor_offset();
    x = get_offset_x(offset);
    y = get_offset_y(offset);
  }

  while (format[index] != 0) {
    if (format[index] == '%') {
      char next_char = format[++index];

      if (next_char == 'x') {
        uint32_t hex = va_arg(args, uint32_t);
        print_hex_32(hex);
      } else if (next_char == 'd') {
        uint32_t num = va_arg(args, uint32_t);
        print_num(num);
      }
    } else {
      print_char_at(format[index], x, y);
    }

    offset = get_cursor_offset();
    x = get_offset_x(offset);
    y = get_offset_y(offset);

    index++;
  }
}

void print_char_at(const char letter, const uint8_t x, const uint8_t y) {
  uint16_t offset = get_offset(x, y);

  switch (letter) {
  case '\n':
    offset = get_offset(0, y + 1);
    set_cursor_offset(offset);
    return;
  }

  vga_entry_t *video_memory = (vga_entry_t *)VIDEO_ADDRESS;

  video_memory[offset].letter = letter;
  video_memory[offset].fg = current_terminal_color.fg;
  video_memory[offset].bg = current_terminal_color.bg;

  set_cursor_offset(offset + 1);
}

void clear_screen() {
  vga_entry_t *video_memory = (vga_entry_t *)VIDEO_ADDRESS;

  for (uint16_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
    video_memory[i].letter = ' ';
    video_memory[i].fg = current_terminal_color.fg;
    video_memory[i].bg = current_terminal_color.bg;
  }

  set_cursor_offset(0);
}

void set_screen_color(const vga_color_entry_t color) {
  current_terminal_color = color;
}

uint16_t get_offset(const uint8_t x, const uint8_t y) {
  return y * VGA_WIDTH + x;
}

uint16_t get_offset_x(const uint16_t offset) { return offset % VGA_WIDTH; }

uint16_t get_offset_y(const uint16_t offset) { return offset / VGA_WIDTH; }

uint16_t get_cursor_offset() {
  uint16_t offset = 0;

  port_byte_out(VGA_SCREEN_CTRL, 14);
  offset += port_byte_in(VGA_SCREEN_DATA) << 8;

  port_byte_out(VGA_SCREEN_CTRL, 15);
  offset += port_byte_in(VGA_SCREEN_DATA);

  return offset;
}

void set_cursor_offset(const uint16_t offset) {
  port_byte_out(VGA_SCREEN_CTRL, 14);
  port_byte_out(VGA_SCREEN_DATA, (uint8_t)(offset >> 8));

  port_byte_out(VGA_SCREEN_CTRL, 15);
  port_byte_out(VGA_SCREEN_DATA, (uint8_t)(offset & 0xFF));
}
