#include <drivers/screen.h>
#include <panic.h>

void panic(const char *cause) {
  set_current_base_attr(RED_ON_WHITE);
  print("KERNEL PANIC: ");
  print(cause);

  while (1) {
    asm volatile("hlt");
  }
}
