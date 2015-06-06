
#include "persistent_stuff.h"

void *serialize_to_new_byte_array(List *list, size_t data_size)
{
// Creates a data blob
void *d = malloc( (data_size * item_count(list)));

if (d == NULL) // Prevent catastrophe
return NULL;
int pos = 0;

int x, cnt = item_count(list);
for (x = 0; x < cnt; x++) // Loop through the list
{
	void *data = get_item_by_index(x, list)->data;
	memcpy((d + pos), data, data_size);
	pos+=data_size;
}

// Done!
return d;

}

void read_from_data_to_list(void *data, size_t data_size, int32_t count, List *list)
{
int x;
for (x = 0; x < count; x++) // Loop through the data
{
	void *d = malloc(data_size); // A byte array to hold the data to be ripped
	if (d == NULL) // Avoid an accident
	return;
	
	// Copy the data
	memcpy(d, ((char *)data + (data_size * x)), data_size);

	// Add the resulting item to the array
	add_item(list, d, -1);
}

}
