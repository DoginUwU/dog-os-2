#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../../cpu/types.h"

void init_keyboard();

typedef struct {
  u8 scancode;
  char character;
} KeyMapping;

typedef struct {
  KeyMapping *mappings;
  int size;
} KeyboardLayout;

void process_scancode(u8 scancode);

#define BACKSPACE 0x0E
#define ENTER 0x1C

#endif
