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

void test_get_frame() {
  uint32_t entry = 0x12345678;
  uint32_t frame = GET_FRAME(&entry);

  TEST_ASSERT_EQUAL_HEX32(frame, 0x12345000);
}

void test_set_frame() {
  uint32_t entry = 0x12345678;
  SET_FRAME(&entry, 0x00123000);

  TEST_ASSERT_EQUAL_HEX32(entry, 0x00123678);
}

void test_get_page_table_entry() {
  page_table_t page_table;
  uint32_t *entry = get_page_table_entry(&page_table, 0x12345678);

  TEST_ASSERT_NOT_NULL(entry);
}

void test_virtual_memory_manager(void) {
  test_page_directory_index();
  test_page_table_index();
  test_get_frame();
  test_set_frame();
  test_get_page_table_entry();
}
