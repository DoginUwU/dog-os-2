#include "panic.h"
#include "drivers/screen.h"

void panic(const char *cause) {
  /*set_current_base_attr(RED_ON_WHITE);*/
  vga_color_entry_t color = {.bg = VGA_COLOR_WHITE, .fg = VGA_COLOR_RED};
  set_screen_color(color);
  print("\nKERNEL PANIC: ");
  print(cause);
  print(" ");
  print(__FILE__);
  print(":");
  print("%d\n", __LINE__);

  while (1) {
    asm volatile("cli;hlt");
  }
}
