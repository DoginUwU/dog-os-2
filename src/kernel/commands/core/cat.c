#include <commands/command.h>
#include <common.h>
#include <drivers/screen.h>
#include <fs/vfs.h>
#include <stddef.h>

int cat_command(char **args) {
  if (args[0] == NULL) {
    print("Missing file param\n");

    return COMMAND_CODE_INVALID_PARAMS;
  }

  fs_node_t *node = vfs_find_node(args[0], FS_FILE);

  if (node == NULL) {
    print("No such file\n");

    return COMMAND_CODE_INVALID_PARAMS;
  }

  char *buffer = vfs_read_file(node);

  if (buffer == NULL) {
    print("Nothing to show :(\n");

    return COMMAND_CODE_SUCCESS;
  }

  print(buffer);

  return COMMAND_CODE_SUCCESS;
}

command_t cat_cmd = {.name = "cat",
                     .description = "Output the source of anything",
                     .execute = cat_command};
