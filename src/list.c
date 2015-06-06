
#include "list.h"

#define hello printf("\nhello\n");

//Creates a new list and returns a pointer to it. Returns NULL upon failure.
List *create_list(void)
{
item *cap;
List *L;
if ((L = malloc(sizeof(List))) == NULL )
return NULL; //Could not allocate memory for the List header.
else
{
if ((cap = malloc(sizeof(item))) == NULL )
return NULL; //Could not allocate memory for the List's cap.
else
{
//Set everything up.
L->First = cap;
cap->data = NULL;
cap->next = (void *)L;
}
}

return L; //If all goes well, a pointer to the new List will be returned.

}

//Destroys a list, all of its items, and its cap.
int destroy_list(List *L)
{
//Delete items
item *i = L->First, *nxt = NULL;
while (i->data != NULL)
{
nxt = i->next;
free(i->data);
free(i);
i = nxt;
}

//Remove cap
free(i);
//Remove header
free(L);
L = NULL;
return 1;
}

//Adds an item to the specified list with the specified data at a specified location. Passing NULL for "location" results in the item being added to the end of the list. Returns NULL upon failure.
item *add_item(List *L, void *data, int location)
{
item *i;
if ((i = malloc(sizeof(item))) == NULL )
return NULL; //Could not allocate memory for the List item.
else
{
//Configure the item's data slot.
i->data = data;
//Proceed to add the item.

//Figure out if an item is already at the needed index
item *item_at_needed_index = get_item_by_index(location, L);
if ((item_at_needed_index == NULL) || location == -1)
{
//It's fine; just add to the end of the list.
if (item_count(L) != 0)
{
item *last_item = get_item_by_index(item_count(L)-1, L);
item *cap = last_item->next;
last_item->next = i;
i->next = cap;
}
else
{
i->next = L->First;
L->First = i;
}
}
else
{
if (location == 0)
{//Add to the top of the list
i->next = L->First;
L->First = i;
}
else
{//Add to another location
item *item_before_needed_index = get_item_by_index(location - 1, L);
item_before_needed_index->next = i;
i->next = item_at_needed_index;
}
}
}
return i;
}

//Finds an item and removes it from the list. Returns 1 upon success, otherwise 0
int remove_item(List *L, item *i)
{
int index = get_item_index(L, i);
if ( index == 0 )
L->First = i->next; //If the item was first in the list
else
{
item *before = get_item_by_index(index - 1, L);
before->next = i->next;
}
free(i->data);
free(i);
return 1;
}

//An implementation of both the remove_item() and get_item_by_index() functions. Returns 1 upon success, otherwise 0
int remove_at(List *L, int index)
{
item *i;
if((i = get_item_by_index(index, L)) != NULL)
{
remove_item(L, i);
return 1;
}
else
return 0;
}

//Returns the number of items in a linked list
int item_count(List *L)
{
item *Next = L->First;
int count = 0;
if ( !is_cap(Next) )
do
{
count++;
Next = Next->next;
}while (!is_cap(Next));
return count;
}

//Retrieves the item in the list that corresponds with (int number). Returns NULL upon failure
item *get_item_by_index(int index, List *L)
{
if ((index < 0) || (index > (item_count(L)-1)))
{
return NULL; //Index is outside of bounds
}
else
{//Index is obtainable.
item *Next = L->First;
int count = 0;
while (count != index)
{
Next = Next->next;
count++;
}
return Next;
}
}

//Retrieves the index of a list item.
int get_item_index(List *L, item *i)
{
int total_list_count = item_count(L);
item *Next = i->next;
int count = 0;
while ( !is_cap(Next) )
{
Next = Next->next;
count++;
}
return (total_list_count - count) - 1;
}

//Searches a linked list for an item; returns NULL upon failure
item *search_for_item(List *L, int (*SearchFunction)(void *data))
{
item *Next = L->First;
while( !is_cap(Next) )
{
if (SearchFunction(Next->data))
return Next;
else
Next = Next->next;
}
if ( is_cap(Next) )
return NULL;
return Next;
}

//Returns a pointer to the header of the list of which the specified item is a part.
List *detect_item_owner(item *i)
{
if (is_cap(i))
return (List *)i->next;
else
{
item *Next = i->next;
while ( !is_cap(Next) )
Next = Next->next;
return (List *)Next->next;
}
}

//Decides whether a specifed item is a cap, and returns its decision. If an error occurs, it returns 0.
int is_cap(item *i)
{
return (i->data == NULL);
}

//Returns a pointer to the data associated with an item with a given index.
void *item_data(List *L, int index)
{
return get_item_by_index(index, L)->data;
}

//Returns a pointer to the data associated with an item.
void *item_data_by_item(item *i)
{
return i->data;
}
