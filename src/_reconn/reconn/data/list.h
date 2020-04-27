#ifndef RECONN_DATA_LIST_H
#define RECONN_DATA_LIST_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "element.h"

typedef struct ReconnList {
  ReconnElement* elements;
  unsigned long top;
  unsigned long reserve;
} ReconnList;

ReconnList* rcn_newReconnList(unsigned long initial_size);

// resize underlying memory of list to given size
void rcn_list_resize(ReconnList* self, unsigned long size);

// check if list is empty
int rcn_list_is_empty(ReconnList* self);

// set element data of list at given index
void rcn_list_set_at(ReconnList* self, unsigned long index,
                     ReconnElement* value);

// get element data of list at given index
ReconnElement* rcn_list_get_at(ReconnList* self, unsigned long index);

// remove element data of list at given index
void rcn_list_remove_at(ReconnList* self, unsigned long index);

// push data at the end of the list (automatically resizes to fit)
void rcn_list_push(ReconnList* self, ReconnElement* value);

// pop element data from end of list
ReconnElement* rcn_list_pop(ReconnList* self, ReconnElement* value);

// find first empty spot in list an insert element data there
unsigned long rcn_list_insert(ReconnList* self, ReconnElement* value);

// set id of element data at given index
void rcn_list_set_id(ReconnList* self, unsigned long index, const char* id);

#endif