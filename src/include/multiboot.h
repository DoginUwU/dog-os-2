#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

typedef struct {
  uint32_t tab_size;
  uint32_t str_size;
  uint32_t address;
  uint32_t reserved;
} multiboot_symbol_table_t;

typedef struct {
  uint32_t num;
  uint32_t size;
  uint32_t address;
  uint32_t shndx;
} multiboot_elf_section_header_table_t;

typedef struct multiboot_info {
  uint32_t flags;
  uint32_t mem_lower;
  uint32_t mem_upper;
  uint32_t boot_device;
  uint32_t cmdline;
  uint32_t mods_count;
  uint32_t mods_addr;

  union {
    multiboot_symbol_table_t aout_sym;
    multiboot_elf_section_header_table_t elf_sec;
  } u;

  uint32_t mmap_length;
  uint32_t mmap_addr;

  uint32_t drives_length;
  uint32_t drives_addr;

  uint32_t config_table;

  uint32_t boot_loader_name;

  uint32_t apm_table;

  uint32_t vbe_control_info;
  uint32_t vbe_mode_info;
  uint16_t vbe_mode;
  uint16_t vbe_interface_seg;
  uint16_t vbe_interface_off;
  uint16_t vbe_interface_len;

  uint64_t framebuffer_addr;
  uint32_t framebuffer_pitch;
  uint32_t framebuffer_width;
  uint32_t framebuffer_height;
  uint8_t framebuffer_bpp;
} multiboot_info_t;

typedef struct multiboot_mmap_entry {
  uint32_t size;
  uint32_t addr_low;
  uint32_t addr_high;
  uint32_t len_low;
  uint32_t len_high;
#define MULTIBOOT_MEMORY_AVAILABLE 1
#define MULTIBOOT_MEMORY_RESERVED 2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE 3
#define MULTIBOOT_MEMORY_NVS 4
#define MULTIBOOT_MEMORY_BADRAM 5
  uint32_t type;
} __attribute__((packed)) multiboot_memory_map_t;

void check_multiboot(multiboot_info_t *boot_info);
multiboot_info_t *get_multiboot_info();
multiboot_memory_map_t *get_multiboot_memory_map(uint32_t index);

#endif
