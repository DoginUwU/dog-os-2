#ifndef PROCESS_H
#define PROCESS_H

#include <fs/vfs.h>

typedef struct {
  fs_node_t *current_directory;
} process_t;

#endif
