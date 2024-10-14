#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../../cpu/types.h"
#include <stdint.h>

void init_keyboard();

typedef struct {
  uint8_t scancode;
  char character;
} KeyMapping;

typedef struct {
  KeyMapping *mappings;
  int size;
} KeyboardLayout;

void process_scancode(uint8_t scancode);

#define BACKSPACE 0x0E
#define ENTER 0x1C

#endif
