#include "keyboard.h"
#include "../../cpu/isr.h"
#include "../../cpu/ports.h"
#include "../../libc/function.h"
#include "../../libc/string.h"
#include "../screen.h"

#include "br_abnt2.h"

char key_buffer[256];

static void keyboard_callback(registers_t *regs) {
  // PIC store the scancode in 0x60
  uint8_t scancode = port_byte_in(0x60);
  process_scancode(scancode);

  UNUSED(regs);
}

// Hint: keydown + 0x80 corresponds to keyup
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

  KeyboardLayout layout = keyboard_br_abnt2;

  for (int i = 0; i < layout.size; i++) {
    if (layout.mappings[i].scancode == scancode) {
      char letter = layout.mappings[i].character;
      char str[2] = {letter, '\0'};
      append(key_buffer, letter);
      print(str);

      return;
    }
  }

  /*print("Key not found for scancode: ");*/
  /*char *sc_ascii;*/
  /*int_to_ascii(scancode, sc_ascii);*/
  /*print(sc_ascii);*/
  /*print("\n");*/
}

void init_keyboard() {
  register_interrupt_handler(IRQ_KEYBOARD, keyboard_callback);
}
