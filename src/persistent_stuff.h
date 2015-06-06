
#include <pebble.h>
#include "list.h"

// Takes a list full of data and serializes it into a new string along with the terminating character.
void *serialize_to_new_byte_array(List *list, size_t data_size);

// Takes abyte array and a list--adds the data to the list
void read_from_data_to_list(void *data, size_t data_size, int32_t count, List *list);
