#include <drivers/screen.h>
#include <lib/logging.h>
#include <lib/string.h>
#include <ports.h>

void log_info(const char *message, ...) {
  va_list args;
  va_start(args, message);
  va_list copy_args;
  va_copy(copy_args, args);

  char current_attr = get_current_base_attr();
  set_current_base_attr(GRAY_ON_BLACK);

  char *full_message = string_concat("[INFO] ", message);
  print_va_list(full_message, copy_args);
  print("\n");

  // TODO: Create free fn to free espace of concatenated strings
  // free(full_message)

  set_current_base_attr(current_attr);

  va_end(args);
}
