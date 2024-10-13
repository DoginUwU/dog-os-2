#include "../drivers/ports.h"

void main() {
  // Scree cursor pos: VGA ports 0x3D4 and get bytes 14 and 15
  port_byte_out(0x3D4, 14);           // Request high byte of cursor pos
  int position = port_byte_in(0x3D5); // Data returned from high byte
  position = position << 8;

  port_byte_out(0x3D4, 15);        // Request low byte of cursor pos
  position += port_byte_in(0x3D5); // Data returned from low byte

  int offset_from_vga = position * 2; // Cells to control data

  char *vga = (char *)0xb8000;
  vga[offset_from_vga] = 'X';
  vga[offset_from_vga + 1] = 0x0F; // White text on black background
}
