#include "timer.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "isr.h"
#include "types.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
  tick++;
  /*print("Tick: ");*/
  /**/
  /*char tick_ascii[256];*/
  /*int_to_ascii(tick, tick_ascii);*/
  /*print(tick_ascii);*/
  /*print("\n");*/
}

void init_timer(u32 freq) {
  register_interrupt_handler(IRQ_COUNTER, timer_callback);

  // PIT value on clock at 1193180Hz
  u32 divisor = 1193180 / freq;
  u8 low = low_8(divisor);
  u8 high = high_8(divisor);

  port_byte_out(0x43, 0x36); // Command Port
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}
