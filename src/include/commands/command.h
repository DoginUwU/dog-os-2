#ifndef COMMAND_H
#define COMMAND_H

typedef struct {
  char *name;
  char *description;
  void (*execute)(char **args);
} command_t;

void init_commands();
void register_command(command_t *command);
int execute_command(char *input);

#endif
