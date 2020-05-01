#include "reconn/data/list.h"

ReconnList* rcn_newReconnList(unsigned long initial_size) {
  ReconnList* self = (ReconnList*)calloc(1, sizeof(*self));
  self->reserve = initial_size;
  self->top = 0;
  self->elements = (ReconnElement*)calloc(self->reserve, sizeof(ReconnElement));
  self->elements[0].kind = RECONN_ELEMENT_VOID;
  return self;
}

void rcn_list_resize(ReconnList* self, unsigned long size) {
  self->elements =
      (ReconnElement*)realloc(self->elements, size * sizeof(ReconnElement));
  self->reserve = size;
}

int rcn_list_is_empty(ReconnList* self) { return !self->top; }

void rcn_list_set_at(ReconnList* self, unsigned long index,
                     ReconnElement* value) {
  assert(index <= self->top);
  self->elements[index].data = value->data;
  self->elements[index].kind = value->kind;
  self->elements[index].id = value->id;
}

ReconnElement* rcn_list_get_at(ReconnList* self, unsigned long index) {
  assert(index <= self->top);
  return (ReconnElement*)&self->elements[index];
}

void rcn_list_remove_at(ReconnList* self, unsigned long index) {
  assert(index < self->reserve);
  self->elements[index].kind = RECONN_ELEMENT_EMPTY;
}

void rcn_list_push(ReconnList* self, ReconnElement* value) {
  if (self->top + 2 > self->reserve) {
    rcn_list_resize(self, self->top + 2);
  }
  self->top++;

  rcn_list_set_at(self, self->top, value);
}

ReconnElement* rcn_list_pop(ReconnList* self, ReconnElement* value) {
  if (self->top) {
    value->data = self->elements[self->top].data;
    value->kind = self->elements[self->top].kind;
    value->id = self->elements[self->top].id;
    self->elements[self->top].kind = RECONN_ELEMENT_EMPTY;
    self->top--;
  } else {
    value->data = NULL;
    value->kind = RECONN_ELEMENT_EMPTY;
    value->id = NULL;
  }
  return value;
}

unsigned long rcn_list_insert(ReconnList* self, ReconnElement* value) {
  for (unsigned long i = 1; i < self->top; i++) {
    if (self->elements[i].kind == RECONN_ELEMENT_EMPTY) {
      rcn_list_set_at(self, i, value);
      return i;
    }
  }
  rcn_list_push(self, value);
  return self->top;
}

void rcn_list_set_id(ReconnList* self, unsigned long index, const char* id) {
  self->elements[self->top].id =
      (char*)realloc(self->elements[self->top].id, strlen(id));
  strcpy(self->elements[self->top].id, id);
}