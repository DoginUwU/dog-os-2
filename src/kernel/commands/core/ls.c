#include <commands/command.h>
#include <common.h>
#include <drivers/screen.h>
#include <fs/vfs.h>
#include <stddef.h>

void ls_command(char **args) {
  fs_node_t *node = vfs_get_current_directory()->children;

  while (node != NULL) {
    print(node->name);

    node = node->next;
    print("\n");
  }

  UNUSED(args);
}

command_t ls_cmd = {"ls", "List files and directories of current location",
                    ls_command};
