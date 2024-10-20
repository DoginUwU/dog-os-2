#include <commands/command.h>
#include <common.h>
#include <drivers/screen.h>
#include <fs/vfs.h>
#include <stddef.h>

int ls_command(char **args) {
  fs_node_t *node = vfs_get_current_directory()->children;

  while (node != NULL) {
    print(node->name);

    node = node->next;
    print("\n");
  }

  UNUSED(args);

  return COMMAND_CODE_SUCCESS;
}

command_t ls_cmd = {.name = "ls",
                    .description =
                        "List files and directories of current location",
                    .execute = ls_command};
