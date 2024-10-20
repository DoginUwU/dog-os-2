
#include <commands/command.h>
#include <common.h>
#include <drivers/screen.h>
#include <fs/vfs.h>
#include <stddef.h>

void cat_command(char **args) {}

command_t cat_cmd = {"cat", "Output the source of anything", cat_command};
