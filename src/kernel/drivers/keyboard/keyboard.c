#include <cpu/idt.h>
#include <cpu/isr.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/screen.h>
#include <lib/string.h>
#include <ports.h>

#include <drivers/keyboard/br_abnt2.h>

void process_scancode(uint8_t scancode);

char key_buffer[256];

static void keyboard_callback(registers_t *regs) {
  uint8_t scancode = port_byte_in(0x60);
  process_scancode(scancode);
}

void process_scancode(uint8_t scancode) {
  if (scancode == BACKSPACE) {
    backspace(key_buffer);
    print_backspace();
    return;
  } else if (scancode == ENTER) {
    print("\n");
    key_buffer[0] = '\0';

    return;
  }

  keyboard_layout_t layout = keyboard_br_abnt2;

  for (size_t i = 0; i < layout.size; i++) {
    if (layout.mappings[i].scancode == scancode) {
      char letter = layout.mappings[i].character;
      char str[2] = {letter, '\0'};

      append(key_buffer, letter);
      print(str);

      return;
    }
  }
}

void init_keyboard() { irq_install_handler(IRQ_KEYBOARD, keyboard_callback); }
