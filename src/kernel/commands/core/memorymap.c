#include <commands/command.h>
#include <common.h>
#include <drivers/screen.h>
#include <fs/vfs.h>
#include <lib/math.h>
#include <lib/memory/phyisical_memory_manager.h>
#include <multiboot.h>
#include <stddef.h>

int memorymap_command(char **args) {
  UNUSED(args);

  multiboot_info_t *boot_info = get_multiboot_info();
  multiboot_memory_map_t *memory_map =
      (multiboot_memory_map_t *)boot_info->mmap_addr;

  for (size_t i = 0; i < boot_info->mmap_length;
       i += sizeof(multiboot_memory_map_t)) {

    print("Size: %x | ", memory_map->addr_low);
    print("Length: %x | ", memory_map->len_low);
    print("Size: %x | ", memory_map->size);

    switch (memory_map->type) {
    case MULTIBOOT_MEMORY_AVAILABLE:
      print("(available)");
      break;
    case MULTIBOOT_MEMORY_RESERVED:
      print("(reserved)");
      break;
    case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
      print("(ACPI reclaimable)");
      break;
    case MULTIBOOT_MEMORY_NVS:
      print("(NVS)");
      break;
    case MULTIBOOT_MEMORY_BADRAM:
      print("(badram)");
      break;
    }

    print("\n");

    memory_map++;
  }

  memory_map--;

  print("\nTotal memory (bytes): %x\n",
        memory_map->addr_low + memory_map->len_low - 1);
  print("Total physical memory blocks (4KB): %x\n", max_blocks);
  print("Total used physical memory blocks (4KB): %x\n", used_blocks);
  print("Total free physical memory blocks (4KB): %x\n",
        max_blocks - used_blocks);

  return COMMAND_CODE_SUCCESS;
}

command_t memorymap_cmd = {.name = "memorymap",
                           .description = "Prints phyisical memory map info",
                           .execute = memorymap_command};
