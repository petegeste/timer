
#if defined ( list_h )
#else
#define list_h
/* LIST.H -- A collection of functions for working with linked lists */

/* NOTE-- the final item in a given linked list will be called a "cap."
   A cap's data item is equal to NULL, and its *next pointer points to
   the list header. A function for verifying whether or not a particular
   list item is a cap has been created. */

#include <malloc.h>
#include <pebble.h>

struct ListItem {
	void *data;
	struct ListItem *next;
};

typedef struct ListItem item;

struct LinkedList {
	item *First;
};

typedef struct LinkedList List;

List *create_list(void); //Creates a new list and returns a pointer to it. Returns NULL upon failure.
int destroy_list(List *L); //Destroys a list, all of its items, and its cap.
item *add_item(List *L, void *data, int location); //Adds an item to the specified list with the specified data at a specified location. Passing NULL for "location" results in the item being added to the end of the list. Returns NULL upon failure.
int remove_item(List *L, item *i); //Finds an item and removes it from the list. A pointer to a function for removing the associated data is also passed; if the pointer is NULL, then removing data will be ignored. Returns 1 upon success, otherwise 0
int remove_at(List *L, int index); //An implementation of both the remove_item() and get_item_by_index() functions. Returns 1 upon success, otherwise 0
int item_count(List *L); //Returns the number of items in a linked list
item *get_item_by_index(int index, List *L); //Retrieves the item in the list that corresponds with (int number). Returns NULL upon failure
int get_item_index(List *L, item *i); //Retrieves the index of a list item.
item *search_for_item(List *L, int (*SearchFunction)(void *data)); //Searches a linked list for an item; returns NULL upon failure
int switch_items(item *item1, item *item2); //Switches the data pointers of two items. Returns 1 upon success; 0 upon failure
void shift_region(List *list, int start_index, int end_index, int shift_by); //Rotates all of the items in a region a specified number of times
List *detect_item_owner(item *i); //Returns a pointer to the header of the list of which the specified item is a part.
int is_cap(item *i); //Decides whether a specifed item is a cap, and returns its decision. If an error occurs, it returns 0.
void *item_data(List *L, int index); //Returns a pointer to the data associated with an item with a given index.
void *item_data_by_item(item *i); //Returns a pointer to the data associated with an item.

#endif
