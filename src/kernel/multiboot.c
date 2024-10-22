#include <common.h>
#include <multiboot.h>
#include <panic.h>
#include <stddef.h>

multiboot_info_t *stored_boot_info = NULL;

void check_multiboot(uint32_t magic_address, multiboot_info_t *boot_info) {
  UNUSED(magic_address);
  /*if (magic_address != MULTIBOOT_MAGIC) {*/
  /*  panic("Multiboot Magic Address is wrong!");*/
  /*}*/

  if (boot_info == NULL) {
    panic("Multiboot info header is missing!");
  }

  if (boot_info->mods_count == 0) {
    panic("No multiboot modules found!");
  }

  if (!(boot_info->flags >> 6 & 0x1)) {
    panic("Invalid memory map by GRUB bootloader");
  }

  stored_boot_info = boot_info;
}

multiboot_info_t *get_multiboot_info() { return stored_boot_info; }

multiboot_memory_map_t *get_multiboot_memory_map(uint32_t index) {
  if (index > stored_boot_info->mmap_length) {
    return NULL;
  }

  if (index % sizeof(multiboot_memory_map_t) != 0) {
    return NULL;
  }

  return (multiboot_memory_map_t *)stored_boot_info->mmap_addr + index;
}
