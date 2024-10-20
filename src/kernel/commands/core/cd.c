#include <commands/command.h>
#include <common.h>
#include <drivers/screen.h>
#include <fs/vfs.h>
#include <stddef.h>

void cd_command(char **args) {
  fs_node_t *directory = vfs_find_node(args[0], FS_DIRECTORY);

  if (directory == NULL) {
    print("No such directory: ");
    print(args[0]);
    print("\n");
    return;
  }

  vfs_change_global_current_directory(directory);
}

command_t cd_cmd = {"cd", "Go to inside some directory", cd_command};
