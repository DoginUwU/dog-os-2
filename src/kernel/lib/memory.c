#include "../../include/lib/memory.h"

void *memcpy(void *dest, const void *src, size_t count) {
  const char *sp = (const char *)src;
  char *dp = (char *)dest;

  for (size_t i = 0; i < count; i++) {
    dp[i] = sp[i];
  }

  return dest;
}

void *memset(void *dest, int val, size_t count) {
  unsigned char *temp = (unsigned char *)dest;

  for (size_t i = 0; i < count; i++) {
    temp[i] = val;
  }

  return dest;
}
