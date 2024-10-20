
#include <commands/command.h>
#include <common.h>
#include <drivers/screen.h>
#include <fs/vfs.h>
#include <stddef.h>

void cat_command(char **args) {
  if (args[0] == NULL) {
    print("Missing file param");
    print("\n");
  }

  fs_node_t *node = vfs_find_node(args[0], FS_FILE);

  if (node == NULL) {
    print("No such file");
    print("\n");
    return;
  }

  char *buffer = vfs_read_file(node);

  if (buffer == NULL) {
    print("Nothing to show :(");
    print("\n");
    return;
  }

  print(buffer);
}

command_t cat_cmd = {"cat", "Output the source of anything", cat_command};
