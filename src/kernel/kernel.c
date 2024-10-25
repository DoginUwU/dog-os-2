#include <commands/command.h>
#include <common.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/timer.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/screen.h>
#include <fs/initrd.h>
#include <fs/vfs.h>
#include <lib/logging.h>
#include <lib/memory/malloc.h>
#include <lib/memory/memory.h>
#include <lib/memory/phyisical_memory_manager.h>
#include <lib/memory/virtual_memory_manager.h>
#include <lib/syscalls.h>
#include <multiboot.h>
#include <panic.h>
#include <shell/shell.h>
#include <stdint.h>

void usermode_main();

void kernel_main(uint32_t magic_address, multiboot_info_t *boot_info) {
  check_multiboot(magic_address, boot_info);

  init_gdt();
  init_idt();

  init_timer(50);
  init_keyboard();

  init_memory_manager();
  init_virtual_memory_manager();

  /*init_shell();*/

  /*uint32_t mod_start = *(uint32_t *)boot_info->mods_addr;*/
  /*uint32_t mod_end = *(uint32_t *)(boot_info->mods_addr + 4);*/
  /**/
  /*uint32_t physical_allocation_start = (mod_end + 0xFFF) & ~0xFFF;*/
  /*print_num(physical_allocation_start);*/
  /*print("\n");*/
  /*print_num(boot_info->mem_lower);*/
  /*print("\n");*/
  /*print_num(boot_info->mem_upper);*/
  /*print("\n");*/
  /**/
  /*fs_node_t *root = vfs_create_directory("/", NULL);*/
  /*vfs_set_root(root);*/
  /*vfs_mount("initrd", root);*/
  /**/
  /*fs_node_t *root_initrd = vfs_create_directory("initrd", root);*/
  /*vfs_mount("initrd", root_initrd);*/
  /*process_initrd(mod_start, root_initrd);*/

  switch_to_user_mode();
  /*usermode_main();*/

  /*init_commands();*/
  /*shell_loop();*/
}

__attribute__((section(".user_text"))) void usermode_main() {
  while (1) {
  }
  /*init_shell();*/

  /*char *str = allocate_blocks(1024 / BLOCK_SIZE);*/
  /*memory_set(str, 0, 1024);*/
  /*str[0] = 'A';*/
  /*str[1] = 'B';*/
  /*str[2] = 'A';*/
  /*str[3] = 'L';*/
  /*str[4] = 'O';*/
  /*str[5] = '\0';*/
  /*print("%s \n", str);*/
  /*free_blocks((uint32_t *)str, 1024 / BLOCK_SIZE);*/
  /*str = allocate_blocks(1024 / BLOCK_SIZE);*/
  /*str[0] = 'O';*/
  /*str[1] = 'V';*/
  /*str[2] = 'O';*/
  /*str[3] = '\0';*/
  /*print("%s \n", str);*/
  /*free_blocks((uint32_t *)str, 1024 / BLOCK_SIZE);*/

  /*init_commands();*/
  /*shell_loop();*/
}
