#include <commands/command.h>
#include <drivers/screen.h>
#include <stddef.h>

void clear_command() { clear_screen(); }

command_t clear_cmd = {"clear", "Clear the entire screen", clear_command};
