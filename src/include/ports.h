#pragma once

#include <stdint.h>

void port_byte_out(const uint16_t port, const uint8_t data);
uint8_t port_byte_in(const uint16_t port);
