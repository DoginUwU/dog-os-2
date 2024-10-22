#include "../unity/unity.h"
#include "lib/memory/test_virtual_memory_manager.h"

void setUp(void) {}

void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_virtual_memory_manager);
  return UNITY_END();
}
