#include "timer.h"
#include "../cpu/ports.h"
#include "../libc/function.h"
#include "isr.h"
#include "types.h"

uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
  tick++;
  /*print("Tick: ");*/
  /**/
  /*char tick_ascii[256];*/
  /*int_to_ascii(tick, tick_ascii);*/
  /*print(tick_ascii);*/
  /*print("\n");*/
  UNUSED(regs);
}

void init_timer(uint32_t freq) {
  register_interrupt_handler(IRQ_COUNTER, timer_callback);

  // PIT value on clock at 1193180Hz
  uint32_t divisor = 1193180 / freq;
  uint8_t low = low_8(divisor);
  uint8_t high = high_8(divisor);

  port_byte_out(0x43, 0x36); // Command Port
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}
