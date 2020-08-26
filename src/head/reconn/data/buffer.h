#ifndef RECONN_DATA_BUFFER_H
#define RECONN_DATA_BUFFER_H

#include "value.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

typedef struct ReconnBufferItem {
  ReconnValueKind kind;
  size_t start;
  size_t stop;
} ReconnBufferItem;

typedef struct ReconnBuffer {
  // end of buffer
  size_t end;
  // number of items in buffer
  size_t count;
  // amount of space reserved for each pointer
  size_t reserved;
  size_t lasti;
  unsigned char *data;
  ReconnBufferItem *items;
} ReconnBuffer;

void reconn_buffer_free(ReconnBuffer *self, int free_self) {
  free(self->data);
  free(self->items);
  if (free_self)
    free(self);
}

ReconnBuffer reconn_makeBuffer() {
  ReconnBuffer self;
  size_t start_reserve = sizeof(ReconnBufferItem);
  self.end = 0;
  self.count = 0;
  self.data = (unsigned char *)malloc(start_reserve);
  self.items = (ReconnBufferItem *)malloc(start_reserve);
  self.reserved = start_reserve;
  self.lasti = 0;
  return self;
}

ReconnBuffer *reconn_newBuffer() {
  ReconnBuffer *self = (ReconnBuffer *)malloc(sizeof(ReconnBuffer));
  *self = reconn_makeBuffer();
  return self;
}

void reconn_buffer_print(ReconnBuffer *self) {
  printf("======\nTOP:%li\nCOUNT:%li\n", self->end, self->count);
  for (size_t i = 0; i < self->count; i++) {
    printf("(%5lu:%5lu)\n", self->items[i].start, self->items[i].stop);
    for (size_t si = self->items[i].start; si < self->items[i].stop; si++) {
      const unsigned char data = self->data[si];
      printf("(%3lu:%5lu) %02x (%3i)[%c]\n", i, si, data, data, data);
    }
    printf("---\n");
  }
}

// ensure each pointer has atleast "minsize" amount of reserved space
void reconn_buffer_resize(ReconnBuffer *self, size_t minsize) {
  // FIXME doesn't handle running out of memory
  while (self->reserved < minsize) {
    size_t newsize = self->reserved * 2;
    self->data = (unsigned char *)realloc(self->data, newsize);
    self->items = (ReconnBufferItem *)realloc(self->items, newsize);

    self->reserved = newsize;
  }
}

void reconn_buffer_grow_for(ReconnBuffer *self, size_t index, size_t size) {
  reconn_buffer_resize(self, sizeof(ReconnBufferItem) * (index + 1));
  reconn_buffer_resize(self, self->end + size);
}

/*
ReconnBuffer *reconn_copyBuffer(ReconnBuffer *source) {
  ReconnBuffer *copy = reconn_newBuffer();

  copy->end = source->end;
  copy->count = source->count;
  // skipping reserved because that would mess with resizing

  // FIXME use "end" instead of reserved
  reconn_buffer_resize(copy, source->end);
  memcpy(copy->data, source->data, source->end);
  memcpy(copy->items, source->items, source->end);

  return copy;
}
*/

/*
=============
PUSHING ITEMS
=============
*/

void reconn_buffer_push_void(ReconnBuffer *self, const void *value, size_t size,
                             ReconnValueKind kind) {
  reconn_buffer_grow_for(self, self->count, size);
  memcpy(&self->data[self->end], value, size);
  self->items[self->count].kind = kind;
  self->items[self->count].start = self->end;
  self->items[self->count].stop = self->end + size;

  self->end += size;
  self->count += 1;

  self->lasti = self->count - 1;
}

/*
=============
GETTING ITEMS
=============
*/

const void *reconn_buffer_get_void(ReconnBuffer *self, size_t index) {
  const size_t start = self->items[index].start;
  // const size_t size = self->items[index].stop - self->items[index].start;
  // void *data = malloc(size);
  // memcpy(data, &self->data[start], size);
  return &self->data[start];
}

/*
=============
POPPING ITEMS
=============
*/

const void *reconn_buffer_pop_void(ReconnBuffer *self) {
  const size_t start = self->items[self->count - 1].start;
  const size_t size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;

  const void *location = (void *)&self->data[start];
  // void *data = reconn_buffer_get_void(self, self->count - 1);

  self->end -= size;
  self->count -= 1;

  self->lasti = self->count - 1;
  return location;
}

/*
==================
UTILLITY FUNCTIONS
==================
*/

unsigned char reconn_buffer_count(ReconnBuffer *self) { return self->count; }

ReconnValueKind reconn_buffer_kind_at(ReconnBuffer *self, unsigned char index) {
  return self->items[index].kind;
}

#endif