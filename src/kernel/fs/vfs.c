#include <drivers/screen.h>
#include <fs/vfs.h>
#include <lib/memory/kmalloc.h>
#include <lib/string.h>
#include <stddef.h>

extern fs_operations_t initrd_operations;
static fs_node_t *global_current_directory = NULL;
fs_node_t *root_mount = NULL;

// TODO: Make this dynamic
fs_t filesystems[] = {
    {.name = "initrd", .operations = &initrd_operations},
    //
};
int num_filesystems = sizeof(filesystems) / sizeof(fs_t);

void vfs_mount(const char *fs_name, fs_node_t *mount_point) {
  for (int i = 0; i < num_filesystems; i++) {
    if (string_compare(fs_name, filesystems[i].name) == 0) {
      mount_point->operations = filesystems[i].operations;
      mount_point->flags = FS_DIRECTORY;
      print("Filesystem loaded: ");
      print(filesystems[i].name);
      print("\n");

      if (root_mount == NULL) {
        root_mount = mount_point;
        global_current_directory = mount_point;
      }

      return;
    }
  }

  print("Filesystem not found: ");
  print(fs_name);
  print("\n");
}

fs_node_t *vfs_create_directory(const char *name) {
  fs_node_t *node = (fs_node_t *)kmalloc(sizeof(fs_node_t));
  node->name = string_copy(name);
  node->size = 0;
  node->flags = FS_DIRECTORY;
  node->data = 0;
  node->parent = root_mount;
  node->next = NULL;

  print("Directory created: ");
  print(node->name);
  print("\n");

  return node;
}

fs_node_t *vfs_create_file(const char *name, uintptr_t data, uint32_t size,
                           fs_node_t *parent) {
  if (parent == NULL) {
    parent = root_mount;
  }

  if ((parent->flags & FS_DIRECTORY) == 0) {
    print("Invalid parent type\n");
    return NULL;
  }

  fs_node_t *node = (fs_node_t *)kmalloc(sizeof(fs_node_t));
  node->name = string_copy(name);
  node->size = size;
  node->flags = FS_FILE;
  node->data = data;
  node->parent = parent;

  if (parent->children == NULL) {
    parent->children = node;
  } else {
    fs_node_t *current = parent->children;
    while (current->next != NULL) {
      current = current->next;
    }

    current->next = node;
  }

  print("File created: ");
  print(parent->name);
  print("/");
  print(node->name);
  print("\n");

  return node;
}
