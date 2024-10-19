#ifndef VFS_H
#define VFS_H

#include <stdint.h>

#define FS_FILE 0x01
#define FS_DIRECTORY 0x02

typedef struct fs_node fs_node_t;

typedef struct {
  int (*open)(fs_node_t *node);
  int (*read)(fs_node_t *node, uint32_t offset, uint32_t size, char *buffer);
  int (*write)(fs_node_t *node, uint32_t offset, uint32_t size,
               const char *buffer);
  int (*mkdir)(fs_node_t *node, const char *name);
} fs_operations_t;

struct fs_node {
  char *name;
  uint32_t size;
  uint32_t flags;
  fs_operations_t *operations;

  struct fs_node *parent;
  struct fs_node *children;
  struct fs_node *next;

  uintptr_t data;
  void *fs_private;
};

typedef struct {
  const char *name;
  fs_operations_t *operations;
} fs_t;

void vfs_mount(const char *fs_name, fs_node_t *mount_point);
fs_node_t *vfs_create_directory(const char *name);
fs_node_t *vfs_create_file(const char *name, uintptr_t data, uint32_t size,
                           fs_node_t *parent);

#endif
