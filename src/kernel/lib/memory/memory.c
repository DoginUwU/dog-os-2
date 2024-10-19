#include <common.h>
#include <cpu/idt.h>
#include <drivers/screen.h>
#include <lib/math.h>
#include <lib/memory/kmalloc.h>
#include <lib/memory/memory.h>
#include <panic.h>
#include <stdint.h>

// kernel directory
extern uint32_t initial_page_dir[PAGE_ENTRIES];

void init_paging() { irq_install_handler(IRQ_PAGE_FAULT, page_fault); }

page_t *get_page(uint32_t address, int make, page_directory_t *directory) {
  address /= PAGE_SIZE;

  uint32_t table_index = address / PAGE_ENTRIES;

  if (directory->tables[table_index]) {
    return &directory->tables[table_index]->pages[address % PAGE_ENTRIES];
  } else if (make) {
    uint32_t tmp;
    directory->tables[table_index] =
        (page_table_t *)kmalloc_align_pysical(sizeof(page_table_t), &tmp);
    memory_set(directory->tables[table_index], 0, PAGE_SIZE);

    directory->tables_physical[table_index] =
        tmp | PAGE_FLAG_PRESENT | PAGE_FLAG_RW;

    return &directory->tables[table_index]->pages[address % PAGE_ENTRIES];
  }

  return 0;
}

void page_fault(registers_t *regs) {
  uint32_t fault_address;
  asm volatile("mov %%cr2, %0" : "=r"(fault_address));

  int present = !(regs->err_code & 0x1);
  int rw = regs->err_code & 0x2;
  int us = regs->err_code & 0x4;
  int reserved = regs->err_code & 0x8;

  print("Page fault! ( ");
  if (present)
    print("present ");
  if (rw)
    print("read-only ");
  if (us)
    print("user-mode ");
  if (reserved)
    print("reserved ");
  print(") at 0x");
  print(int_to_hex(fault_address));
  print("\n");

  panic("Page fault");
}

void memory_copy(uint8_t *src, uint8_t *dest, size_t count) {
  for (size_t i = 0; i < count; i++) {
    *(dest + i) = *(src + i);
  }
}

void *memory_set(void *dest, int val, size_t count) {
  unsigned char *temp = (unsigned char *)dest;

  for (size_t i = 0; i < count; i++) {
    temp[i] = val;
  }

  return dest;
}
