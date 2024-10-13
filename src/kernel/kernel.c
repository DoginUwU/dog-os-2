#include "../drivers/screen.h"
#include "util.h"

void main() {
  clear_screen();

  int i = 0;

  for (i = 0; i < 24; i++) {
    char str[255];
    int_to_ascii(i, str);
    print_at(str, 0, i);
  }
}
