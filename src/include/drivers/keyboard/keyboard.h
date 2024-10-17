#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stddef.h>
#include <stdint.h>

void init_keyboard();

typedef struct {
  uint8_t scancode;
  char character;
} key_mapping_t;

typedef struct {
  key_mapping_t *mappings;
  size_t size;
} keyboard_layout_t;

#define BACKSPACE 0x0E
#define ENTER 0x1C

#endif
