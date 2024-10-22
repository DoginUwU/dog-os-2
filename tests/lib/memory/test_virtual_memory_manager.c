#include "../../../unity/unity.h"
#include <lib/memory/virtual_memory_manager.h>

void test_page_directory_index() {
  uint32_t address = 0x00400000;
  uint32_t index = PAGE_DIRECTORY_INDEX(address);

  TEST_ASSERT_EQUAL_HEX32(index, 1);

  address = 0x00000000;
  index = PAGE_DIRECTORY_INDEX(address);

  TEST_ASSERT_EQUAL_HEX32(index, 0);
}

void test_page_table_index() {
  uint32_t address = 0xC1234567;
  uint32_t index = PAGE_TABLE_INDEX(address);

  TEST_ASSERT_EQUAL_HEX32(index, 0x234);
}

void test_virtual_memory_manager(void) {
  test_page_directory_index();
  test_page_table_index();
}
