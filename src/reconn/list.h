#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

#include "element.h"

typedef struct List {
  Element* elements;
  unsigned long top;
  unsigned long reserve;
} List;

List* newList(unsigned long initial_size) {
  List* self = (List*)calloc(1, sizeof(*self));
  self->reserve = initial_size;
  self->top = 0;
  self->elements = (Element*)calloc(self->reserve, sizeof(Element));
  self->elements[0].kind = ELEMENT_VOID;
  return self;
}

void list_resize(List* self, unsigned long size) {
  self->elements = (Element*)realloc(self->elements, size * sizeof(Element));
  self->reserve = size;
}

int list_is_empty(List* self) { return !self->top; }

void list_set_at(List* self, unsigned long index, Element* value) {
  assert(index <= self->top);
  self->elements[index].data = value->data;
  self->elements[index].kind = value->kind;
  self->elements[index].id = value->id;
}

Element* list_get_at(List* self, unsigned long index) {
  assert(index <= self->top);
  return (Element*)&self->elements[index];
}

void list_remove_at(List* self, unsigned long index) {
  assert(index < self->reserve);
  self->elements[index].kind = ELEMENT_EMPTY;
}

void list_push(List* self, Element* value) {
  if (self->top + 2 > self->reserve) {
    list_resize(self, self->top + 2);
  }
  self->top++;

  list_set_at(self, self->top, value);
}

Element* list_pop(List* self, Element* value) {
  if (self->top) {
    value->data = self->elements[self->top].data;
    value->kind = self->elements[self->top].kind;
    value->id = self->elements[self->top].id;
    self->elements[self->top].kind = ELEMENT_EMPTY;
    self->top--;
  } else {
    value->data = NULL;
    value->kind = ELEMENT_EMPTY;
    value->id = NULL;
  }
  return value;
}

unsigned long list_insert(List* self, Element* value) {
  for (unsigned long i = 1; i < self->top; i++) {
    if (self->elements[i].kind == ELEMENT_EMPTY) {
      list_set_at(self, i, value);
      return i;
    }
  }
  list_push(self, value);
  return self->top;
}

void list_set_id(List* self, unsigned long index, const char* id) {
  self->elements[self->top].id =
      (char*)realloc(self->elements[self->top].id, strlen(id));
  strcpy(self->elements[self->top].id, id);
}

#endif