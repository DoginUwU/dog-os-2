#include "../include/ports.h"

void port_byte_out(uint16_t port, uint8_t data) {
  __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

uint8_t port_byte_in(uint16_t port) {
  uint8_t result;
  __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
  return result;
}

void port_word_out(uint16_t port, uint16_t data) {
  __asm__ volatile("outw %0, %1" : : "a"(data), "Nd"(port));
}

uint16_t port_word_in(uint16_t port) {
  uint16_t result;
  __asm__ volatile("inw %1, %0" : "=a"(result) : "Nd"(port));
  return result;
}
