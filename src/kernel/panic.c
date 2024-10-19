#include <drivers/screen.h>
#include <panic.h>

void panic(const char *cause) {
  set_current_base_attr(RED_ON_WHITE);
  print("KERNEL PANIC: ");
  print(cause);
  print(" ");
  print(__FILE__);
  print(":");
  print_num(__LINE__);

  while (1) {
    asm volatile("hlt");
  }
}
