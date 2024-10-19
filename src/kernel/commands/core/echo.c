#include <commands/command.h>
#include <drivers/screen.h>
#include <stddef.h>

void echo_command(char **args) {
  for (int i = 0; args[i] != NULL; i++) {
    print(args[i]);
    print(" ");
  }
}

command_t echo_cmd = {"echo", "Display the output of args", echo_command};
