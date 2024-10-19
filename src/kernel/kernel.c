#include <commands/command.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/timer.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/screen.h>
#include <lib/kmalloc.h>
#include <lib/memory.h>
#include <multiboot.h>
#include <shell/shell.h>

void kernel_main(uint32_t magic_address, multiboot_info_t *boot_info) {
  init_gdt();
  init_idt();

  init_timer(50);
  init_keyboard();

  uint32_t mod1 = *(uint32_t *)(boot_info->mods_addr + 4);
  uint32_t physical_allocation_start = (mod1 + 0xFFF) & ~0xFFF;

  init_memory(physical_allocation_start, boot_info->mem_upper * 1024);

  init_shell();
  init_commands();
  shell_loop();
}
