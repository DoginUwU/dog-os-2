#include <commands/command.h>
#include <common.h>
#include <drivers/screen.h>
#include <fs/vfs.h>
#include <stddef.h>

extern fs_node_t *global_current_directory;

void ls_command(char **args) {
  fs_node_t *node = global_current_directory->children;

  while (node != NULL) {
    print(node->name);

    node = node->next;

    if (node != NULL) {
      print("\n");
    }
  }

  UNUSED(args);
}

command_t ls_cmd = {"ls", "List files and directories of current location",
                    ls_command};
