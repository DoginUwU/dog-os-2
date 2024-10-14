#include "keyboard.h"
#include "../../cpu/isr.h"
#include "../../cpu/ports.h"
#include "../screen.h"

#include "br_abnt2.h"

static void keyboard_callback(registers_t regs) {
  // PIC store the scancode in 0x60
  u8 scancode = port_byte_in(0x60);
  process_scancode(scancode);
}

// Hint: keydown + 0x80 corresponds to keyup
void process_scancode(u8 scancode) {
  KeyboardLayout layout = keyboard_br_abnt2;

  for (int i = 0; i < layout.size; i++) {
    if (layout.mappings[i].scancode == scancode) {
      print("achei");
      print("\n");

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
