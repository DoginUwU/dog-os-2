#include "memory.h"

void memory_copy(char *source, char *dest, int nbytes) {
  for (int i = 0; i < nbytes; i++) {
    *(dest + i) = *(source + i);
  }
}

void memory_set(void *dest, u8 val, u32 len) {
  u8 *temp = dest;

  for (; len > 0; len--) {
    *temp++ = val;
  }
}
