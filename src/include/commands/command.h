#ifndef COMMAND_H
#define COMMAND_H

#define COMMAND_CODE_SUCCESS (1 << 0)
#define COMMAND_CODE_INVALID_PARAMS (1 << 1)

typedef struct {
  char *name;
  char *description;
  int (*execute)(char **args);
} command_t;

void init_commands();
void register_command(command_t *command);
int execute_command(char *input);

#endif
