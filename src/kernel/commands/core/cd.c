#include <commands/command.h>
#include <common.h>
#include <drivers/screen.h>
#include <fs/vfs.h>
#include <stddef.h>

int cd_command(char **args) {
  fs_node_t *directory = vfs_find_node(args[0], FS_DIRECTORY);

  if (directory == NULL) {
    print("No such directory: ");
    print(args[0]);
    print("\n");

    return COMMAND_CODE_INVALID_PARAMS;
  }

  vfs_change_global_current_directory(directory);

  return COMMAND_CODE_SUCCESS;
}

command_t cd_cmd = {.name = "cd",
                    .description = "Go to inside some directory",
                    .execute = cd_command};
