#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include <stdint.h>

typedef void *type_t;

typedef int (*predicate_t)(type_t, type_t);
typedef struct {
  type_t *array;
  uint32_t size;
  uint32_t max_size;
  predicate_t less_than;
} ordered_array_t;

int default_less_than_predicate(type_t a, type_t b);
ordered_array_t create_ordered_array(uint32_t max_size, predicate_t less_than);
ordered_array_t place_ordered_array(void *address, uint32_t max_size,
                                    predicate_t less_than);
void destroy_ordered_array(ordered_array_t *array);
void insert_ordered_array(ordered_array_t *array, type_t item);
void remove_from_ordered_array(ordered_array_t *array, uint32_t index);
type_t find_into_ordered_array(ordered_array_t *array, uint32_t index);

#endif
