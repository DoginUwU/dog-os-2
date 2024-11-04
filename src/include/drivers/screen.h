#pragma once

#include <stdint.h>

#define VIDEO_ADDRESS = 0xB8000;
#define WHITE_BLACK = 0x0F

void print_char_at(const char letter, const uint8_t x, const uint8_t y);
