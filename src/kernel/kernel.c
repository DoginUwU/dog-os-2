#include <commands/command.h>
#include <common.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/timer.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/screen.h>
#include <fs/initrd.h>
#include <fs/vfs.h>
#include <lib/memory/kmalloc.h>
#include <lib/memory/memory.h>
#include <multiboot.h>
#include <panic.h>
#include <shell/shell.h>

void kernel_main(uint32_t magic_address, multiboot_info_t *boot_info) {
  UNUSED(magic_address);
  /*if (magic_address != MULTIBOOT_MAGIC) {*/
  /*  panic("Multiboot Magic Address is wrong!");*/
  /*}*/

  init_gdt();
  init_idt();
  setup_paging();

  init_timer(50);
  init_keyboard();

  if (!boot_info) {
    panic("Multiboot info header is missing!");
  }

  if (boot_info->mods_count == 0) {
    print("No multiboot modules found!");
  }

  init_shell();

  uint32_t mod_start = *(uint32_t *)boot_info->mods_addr;
  /*uint32_t mod_end = *(uint32_t *)(boot_info->mods_addr + 4);*/

  /*uint32_t physical_allocation_start = (mod_end + 0xFFF) & ~0xFFF;*/
  /*print_num(physical_allocation_start);*/
  /*print("\n");*/
  /*print_num(boot_info->mem_lower);*/
  /*print("\n");*/
  /*print_num(boot_info->mem_upper);*/
  /*print("\n");*/

  fs_node_t *root = vfs_create_directory("/", NULL);
  vfs_set_root(root);
  vfs_mount("initrd", root);

  fs_node_t *root_initrd = vfs_create_directory("initrd", root);
  vfs_mount("initrd", root_initrd);
  process_initrd(mod_start, root_initrd);

  init_commands();
  shell_loop();
}
