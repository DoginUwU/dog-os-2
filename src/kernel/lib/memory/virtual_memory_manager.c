#include <lib/memory/virtual_memory_manager.h>
#include <stddef.h>

page_table_entry *get_page_table_entry(page_table_t *page_table,
                                       const virtual_address address) {
  if (page_table) {
    return &page_table->entries[PAGE_TABLE_INDEX(address)];
  }

  return NULL;
}

page_directory_entry *get_page_directory_entry(page_directory_t *page_directory,
                                               const virtual_address address) {
  if (page_directory) {
    return &page_directory->entries[PAGE_TABLE_INDEX(address)];
  }

  return NULL;
}

page_table_entry *get_page(const virtual_address address) {
  // Find page directory
  page_directory_t *page_directory = current_page_directory;

  // Find table in directory
  page_directory_entry *directory_entry =
      &page_directory->entries[PAGE_DIRECTORY_INDEX(address)];
  page_table_t *page_table = (page_table_t *)GET_FRAME(directory_entry);

  // Find page in table
  page_table_entry *page_entry =
      &page_table->entries[PAGE_TABLE_INDEX(address)];

  return page_entry;
}

void *allocate_page(page_table_entry *page_entry) { return NULL; }
