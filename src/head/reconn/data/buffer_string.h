#ifndef RECONN_DATA_BUFFER_STRING_H
#define RECONN_DATA_BUFFER_STRING_H

#include "buffer.h"
#include "string.h"
#include "value.h"
//#include "limits.h"

/*
=============
PUSHING ITEMS
=============
*/

void reconn_buffer_push_cstring(ReconnBuffer *self, const char *value) {
  const size_t size = strlen(value) + 1;
  // printf("WANTS ALLOC >%s<\n", value);
  reconn_buffer_push_void(self, value, size, RECONN_VALUE_C_STRING);
}

void reconn_buffer_push_bytestring(ReconnBuffer *self, const char *value,
                                   size_t size) {
  reconn_buffer_push_void(self, value, size, RECONN_VALUE_BYTE_STRING);
}

/*
=============
GETTING ITEMS
=============
*/

char *reconn_buffer_get_cstring(ReconnBuffer *self, size_t index) {
  // const size_t start = self->items[index].start;
  const size_t size = self->items[index].stop - self->items[index].start;
  const char *location = (const char *)reconn_buffer_get_void(self, index);
  char *result = (char *)malloc(size);
  memcpy(result, location, size);
  return result;
}

char *reconn_buffer_get_bytestring(ReconnBuffer *self, size_t index) {
  // const size_t start = self->items[index].start;
  const size_t size = self->items[index].stop - self->items[index].start;
  const char *location = (const char *)reconn_buffer_get_void(self, index);
  char *result = (char *)malloc(size);
  memcpy(result, location, size);
  return result;
}

/*
=============
POPPING ITEMS
=============
*/

char *reconn_buffer_pop_cstring(ReconnBuffer *self) {
  const size_t size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  const char *location = (const char *)reconn_buffer_pop_void(self);
  char *result = (char *)malloc(size);
  memcpy(result, location, size);
  return result;
}

char *reconn_buffer_pop_bytestring(ReconnBuffer *self) {
  const size_t size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  const char *location = (const char *)reconn_buffer_pop_void(self);
  char *result = (char *)malloc(size);
  memcpy(result, location, size);
  return result;
}

#endif