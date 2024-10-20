#include <commands/command.h>
#include <drivers/screen.h>
#include <stddef.h>

int clear_command() {
  clear_screen();
  return COMMAND_CODE_SUCCESS;
}

command_t clear_cmd = {.name = "clear",
                       .description = "Clear the entire screen",
                       .execute = clear_command};
