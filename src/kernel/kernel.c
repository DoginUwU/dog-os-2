#include <commands/command.h>
#include <common.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/timer.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/screen.h>
#include <lib/initrd.h>
#include <lib/kmalloc.h>
#include <lib/memory.h>
#include <multiboot.h>
#include <panic.h>
#include <shell/shell.h>

void kernel_main(uint32_t magic_address, multiboot_info_t *boot_info) {
  /*if (magic_address != MULTIBOOT_MAGIC) {*/
  /*  panic("Multiboot Magic Address is wrong!");*/
  /*}*/

  init_gdt();
  init_idt();

  init_timer(50);
  init_keyboard();

  if (!boot_info) {
    panic("Multiboot info header is missing!");
  }

  if (boot_info->mods_count == 0) {
    print("No multiboot modules found!");
  }

  uint32_t mod_start = *(uint32_t *)boot_info->mods_addr;
  uint32_t mod_end = *(uint32_t *)(boot_info->mods_addr + 4);

  init_shell();
  process_initrd(mod_start);

  uint32_t physical_allocation_start = (mod_end + 0xFFF) & ~0xFFF;
  init_memory(physical_allocation_start, boot_info->mem_upper * 1024);

  init_commands();
  shell_loop();
}
