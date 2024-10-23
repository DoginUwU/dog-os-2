#include "../unity/unity.h"
#include "lib/memory/test_virtual_memory_manager.h"

extern void jump_usermode() {}
uint32_t kernel_virtual_end = 0;

void setUp(void) {}

void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_virtual_memory_manager);
  return UNITY_END();
}
