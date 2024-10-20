#include <commands/command.h>
#include <drivers/screen.h>
#include <stddef.h>

int echo_command(char **args) {
  for (int i = 0; args[i] != NULL; i++) {
    print(args[i]);
    print(" ");
  }

  print("\n");

  return COMMAND_CODE_SUCCESS;
}

command_t echo_cmd = {.name = "echo",
                      .description = "Display the output of args",
                      .execute = echo_command};
