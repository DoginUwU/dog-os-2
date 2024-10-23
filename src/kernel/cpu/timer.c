#include <common.h>
#include <cpu/idt.h>
#include <cpu/isr.h>
#include <cpu/timer.h>
#include <drivers/screen.h>
#include <ports.h>
#include <stdint.h>

uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
  tick++;

  print("tick: ");
  print_num(tick);
  print("\n");
  UNUSED(regs);
}

void init_timer(uint32_t freq) {
  irq_install_handler(IRQ_TIMER, timer_callback);

  uint32_t divisor = 1193180 / freq;
  uint8_t low = (uint8_t)(divisor & 0xFF);
  uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

  port_byte_out(0x43, 0x36);
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}
