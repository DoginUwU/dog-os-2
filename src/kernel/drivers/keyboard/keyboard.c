#include <cpu/idt.h>
#include <cpu/isr.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/screen.h>
#include <lib/string.h>
#include <ports.h>

#include <drivers/keyboard/br_abnt2.h>

extern void call_shell_keyboard_key_press(char key);

char process_scancode(uint8_t scancode);

static void keyboard_callback(registers_t *regs) {
  uint8_t scancode = port_byte_in(0x60);
  char key = process_scancode(scancode);

  call_shell_keyboard_key_press(key);
}

char process_scancode(uint8_t scancode) {
  keyboard_layout_t layout = keyboard_br_abnt2;

  for (size_t i = 0; i < layout.size; i++) {
    if (layout.mappings[i].scancode == scancode) {
      char key = layout.mappings[i].character;

      return key;
    }
  }

  return '\0';
}

void init_keyboard() {
  irq_install_handler(IRQ_KEYBOARD, keyboard_callback);
  //
}
