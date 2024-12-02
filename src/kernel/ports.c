#include "ports.h"

void port_byte_out(const uint16_t port, const uint8_t data) {
  __asm__("outb %%al, %%dx" : : "a"(data), "d"(port));
}

uint8_t port_byte_in(const uint16_t port) {
  uint8_t result;
  __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
  return result;
}
