#include <commands/command.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/screen.h>
#include <lib/string.h>
#include <shell/shell.h>

void read_command();

char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
int buffer_pos = 0;
int buffer_ready = 0;
int listen_for_user_commands = 1;

void init_shell() {
  clear_screen();
  print("Welcome to DogOS v0.1\n");
  print("This build is unstable and may have some issues!\n\n");
}

void shell_loop() { read_command(); }

void read_command() {
  print("> ");

  while (1) {
    if (buffer_ready == 1) {
      buffer_ready = 0;
      print("\n");
      int executed = execute_command(keyboard_buffer);
      if (executed == 1) {
        print("\n");
      } else if (keyboard_buffer[0] != '\0') {
        print("command not found: ");
        print(keyboard_buffer);
        print("\n");
      }
      break;
    }
  }

  if (listen_for_user_commands == 1) {
    read_command();
  }
}

void call_shell_keyboard_key_press(char key) {
  if (key == 0) {
    return;
  }

  if (key == '\n') {
    keyboard_buffer[buffer_pos] = '\0';

    buffer_ready = 1;
    buffer_pos = 0;
  } else if (key == '\b') {
    if (buffer_pos > 0) {
      backspace(keyboard_buffer);
      print_backspace();
      buffer_pos--;
    }
  } else if (buffer_pos < KEYBOARD_BUFFER_SIZE) {
    keyboard_buffer[buffer_pos++] = key;

    char str[2] = {key, '\0'};
    print(str);
  }
}
