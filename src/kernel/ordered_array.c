#include <lib/memory/kmalloc.h>
#include <lib/memory/memory.h>
#include <ordered_array.h>

// TODO: Make better ordered array algorithm

int default_less_than_predicate(type_t a, type_t b) { return (a < b) ? 1 : 0; }

ordered_array_t create_ordered_array(uint32_t max_size, predicate_t less_than) {
  ordered_array_t new_array;

  size_t array_size = max_size * sizeof(type_t);
  new_array.array = (void *)kmalloc(array_size);
  memory_set(new_array.array, 0, array_size);

  new_array.size = 0;
  new_array.max_size = max_size;
  new_array.less_than = less_than;

  return new_array;
}

ordered_array_t place_ordered_array(void *address, uint32_t max_size,
                                    predicate_t less_than) {
  ordered_array_t new_array;

  new_array.array = (type_t *)address;
  memory_set(new_array.array, 0, max_size * sizeof(type_t));

  new_array.size = 0;
  new_array.max_size = max_size;
  new_array.less_than = less_than;

  return new_array;
}

void destroy_ordered_array(ordered_array_t *array) {
  // TODO: Add kfree method
  // kfree(array->array);
}

void insert_ordered_array(ordered_array_t *array, type_t item) {
  if (array->less_than == NULL) {
    // TODO: Add log system
    return;
  }

  uint32_t i = 0;
  while (i < array->size && array->less_than(array->array[i], item)) {
    i++;
  }

  if (i == array->size) { // Add at the end of array
    array->array[array->size++] = item;
  } else {
    type_t temp = array->array[i]; // Get the current item in array to shift it
    array->array[i] = item;        // Place the new item into found index

    while (i < array->size) { // Shift the rest to the right
      i++;

      type_t temp2 = array->array[i];
      array->array[i] = temp;
      temp = temp2;
    }

    array->size++; // Increase the current size
  }
}

void remove_from_ordered_array(ordered_array_t *array, uint32_t index) {
  while (index < array->size) {
    array->array[index] = array->array[index + 1];
  }

  array->size--;
}

type_t find_into_ordered_array(ordered_array_t *array, uint32_t index) {
  if (index > array->size) {
    // TODO: Add log system
    return NULL;
  }

  return array->array[index];
}
