#include "gdt.h"

struct gdt_entry gdt_entries[5]; // NULL | Code | Data | User Code | User Data
struct gdt_ptr gp;

extern void gdt_flush();

static void static_init_gdt();

static void gdt_set_entry(int num, uint32_t base, uint32_t limit,
                          uint8_t access, uint8_t gran) {
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;

  gdt_entries[num].limit_low = (limit & 0xFFFF);
  gdt_entries[num].granularity = (limit >> 16) & 0x0F;

  gdt_entries[num].granularity |= gran & 0xF0;
  gdt_entries[num].access = access;
}

void init_gdt() { static_init_gdt(); }

static void static_init_gdt() {
  gdt_set_entry(0, 0, 0, 0, 0);
  gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

  gdt_flush((uint32_t)&gp);
}
