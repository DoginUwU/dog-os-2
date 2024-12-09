#pragma once

#include <stdint.h>

#define VIDEO_ADDRESS 0xB8000

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_SCREEN_CTRL 0x3D4
#define VGA_SCREEN_DATA 0x3D5

enum VgaColor {
  VGA_COLOR_BLACK = 0, //
  VGA_COLOR_RED = 4,
  VGA_COLOR_GRAY = 7,
  VGA_COLOR_WHITE = 15
};

typedef struct VgaColorEntry {
  unsigned int fg : 4;
  unsigned int bg : 4;
} __attribute__((packed)) vga_color_entry_t;

typedef struct VgaEntry {
  char letter;
  unsigned int fg : 4;
  unsigned int bg : 4;
} __attribute__((packed)) vga_entry_t;

void set_screen_color(const vga_color_entry_t color);
void print_char_at(const char letter, const uint8_t x, const uint8_t y);
void println(const char *format, ...);
void print(const char *format, ...);
void clear_screen();
