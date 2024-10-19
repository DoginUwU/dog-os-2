#include <commands/command.h>
#include <drivers/screen.h>
#include <lib/memory.h>
#include <lib/string.h>
#include <stddef.h>

#define MAX_COMMANDS 100
#define MAX_ARGS 10

command_t *commands[MAX_COMMANDS];
int command_count = 0;

extern command_t echo_cmd;

void init_commands() { register_command(&echo_cmd); }

void register_command(command_t *command) {
  if (command_count < MAX_COMMANDS) {
    commands[command_count++] = command;
  }
}

int execute_command(char *input) {
  char *command_name = string_truncate(input, " ");

  if (command_name == NULL) {
    return 0;
  }

  for (int i = 0; i < command_count; i++) {
    if (string_compare(command_name, commands[i]->name) == 0) {
      int arg_count = 0;
      char *args[MAX_ARGS + 1];

      memory_set(args, 0, MAX_ARGS * sizeof(char *));

      char *arg = string_truncate(NULL, " ");
      while (arg != NULL && arg_count < MAX_ARGS) {
        args[arg_count++] = arg;
        arg = string_truncate(NULL, " ");
      }

      args[arg_count] = NULL;
      commands[i]->execute(args);

      return 1;
    }
  }

  return 0;
}
