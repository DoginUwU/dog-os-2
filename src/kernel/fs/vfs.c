#include <drivers/screen.h>
#include <fs/vfs.h>
#include <lib/memory/kmalloc.h>
#include <lib/string.h>
#include <stddef.h>

extern fs_operations_t initrd_operations;
fs_node_t *global_current_directory = NULL;
fs_node_t *root_mount = NULL;

// TODO: Make this dynamic
fs_t filesystems[] = {
    {.name = "initrd", .operations = &initrd_operations},
    //
};
int num_filesystems = sizeof(filesystems) / sizeof(fs_t);

void vfs_set_root(fs_node_t *mount_point) {
  print("New root mount: ");
  print(mount_point->name);
  print("\n");

  root_mount = mount_point;
  global_current_directory = mount_point;
}

void vfs_mount(const char *fs_name, fs_node_t *mount_point) {
  for (int i = 0; i < num_filesystems; i++) {
    if (string_compare(fs_name, filesystems[i].name) == 0) {
      mount_point->operations = filesystems[i].operations;
      mount_point->flags = FS_DIRECTORY;
      print("Filesystem loaded: ");
      print(filesystems[i].name);
      print(" into ");
      print(mount_point->name);
      print("\n");

      return;
    }
  }

  print("Filesystem not found: ");
  print(fs_name);
  print("\n");
}

fs_node_t *vfs_create_directory(const char *name, fs_node_t *parent) {
  if (parent == NULL) {
    parent = root_mount;
  }

  if ((parent->flags & FS_DIRECTORY) == 0) {
    print("Invalid parent type\n");
    return NULL;
  }

  fs_node_t *node = (fs_node_t *)kmalloc(sizeof(fs_node_t));

  node->name = string_copy(name);
  node->size = 0;
  node->flags = FS_DIRECTORY;
  node->data = 0;
  node->parent = parent;
  node->next = NULL;
  node->children = NULL;
  node->operations = NULL;

  if (parent->children == NULL) {
    parent->children = node;
  } else {
    fs_node_t *current = parent->children;
    while (current->next != NULL) {
      current = current->next;
    }

    current->next = node;
  }

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
  node->children = NULL;
  node->next = NULL;
  node->operations = NULL;

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

fs_node_t *vfs_find_node(const char *path, uint32_t flags) {
  char *truncated_path = string_truncate(path, "/");

  fs_node_t *current_node = global_current_directory->children;

  if (truncated_path == NULL) {
    truncated_path = string_copy(path);
  }

  while (truncated_path != NULL) {
    if (current_node == NULL) {
      return NULL;
    }

    if ((current_node->flags & flags) == 0) {
      current_node = current_node->next;
      continue;
    }

    if (string_compare(truncated_path, current_node->name) == 0) {
      truncated_path = string_truncate(NULL, "/");

      if (truncated_path == NULL) {
        return current_node;
      } else {
        current_node = current_node->children;
      }
    } else {
      current_node = current_node->next;
    }
  }

  return current_node;
}

void vfs_change_global_current_directory(fs_node_t *new_directory) {
  if ((new_directory->flags & FS_DIRECTORY) == 0) {
    print("File is not a directory!\n");
    return;
  }

  global_current_directory = new_directory;
}

fs_node_t *vfs_get_current_directory() { return global_current_directory; }

fs_node_t *vfs_get_mount_node(fs_node_t *node) {
  fs_node_t *mount_of_node = node;

  while (mount_of_node->operations == NULL) {
    if (mount_of_node->parent != NULL) {
      mount_of_node = mount_of_node->parent;
      return mount_of_node;
    } else {
      print("Node: ");
      print(mount_of_node->name);
      print(" has no parent\n");
      break;
    }
  }

  return NULL;
}

char *vfs_read_file(fs_node_t *node) {
  fs_node_t *mount_node = vfs_get_mount_node(node);

  if (mount_node == NULL) {
    return NULL;
  }

  return mount_node->operations->read(node, 0, node->size);
}
