#include <drivers/screen.h>
#include <drivers/timer.h>
#include <idt.h>
#include <isr.h>
#include <ports.h>

uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
  tick++;
  print("Tick: ");
  print_num(tick);
}

void init_timer(uint32_t freq) {
  register_interrupt_handler(IRQ_COUNTER, &timer_callback);

  uint32_t divisor = 1193180 / freq;

  port_byte_out(0x43, 0x36);

  uint32_t low = low_8(divisor);
  uint32_t high = high_8(divisor);

  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}
