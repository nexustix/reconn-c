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

static void reconn_buffer_finalize_push(ReconnBuffer *self,
                                        ReconnValueKind kind,
                                        unsigned short size) {
  self->items[self->count].kind = kind;
  self->items[self->count].start = self->end;
  self->items[self->count].stop = self->end + size;

  self->end += size;
  self->count += 1;
}

void reconn_buffer_push_u8(ReconnBuffer *self, unsigned char value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  unsigned char *location = (unsigned char *)&self->data[self->end];
  *location = value;
  reconn_buffer_finalize_push(self, RECONN_VALUE_U8, sizeof(value));
}

void reconn_buffer_push_u16(ReconnBuffer *self, unsigned short value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  unsigned short *location = (unsigned short *)&self->data[self->end];
  *location = value;
  reconn_buffer_finalize_push(self, RECONN_VALUE_U16, sizeof(value));
}

void reconn_buffer_push_u32(ReconnBuffer *self, unsigned long value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  unsigned long *location = (unsigned long *)&self->data[self->end];
  *location = value;
  reconn_buffer_finalize_push(self, RECONN_VALUE_U32, sizeof(value));
}

void reconn_buffer_push_u64(ReconnBuffer *self, unsigned long long value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  unsigned long long *location = (unsigned long long *)&self->data[self->end];
  *location = value;
  reconn_buffer_finalize_push(self, RECONN_VALUE_U64, sizeof(value));
}

void reconn_buffer_push_s8(ReconnBuffer *self, char value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  char *location = (char *)&self->data[self->end];
  *location = value;
  reconn_buffer_finalize_push(self, RECONN_VALUE_S8, sizeof(value));
}

void reconn_buffer_push_s16(ReconnBuffer *self, short value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  short *location = (short *)&self->data[self->end];
  *location = value;
  reconn_buffer_finalize_push(self, RECONN_VALUE_S16, sizeof(value));
}

void reconn_buffer_push_s32(ReconnBuffer *self, long value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  long *location = (long *)&self->data[self->end];
  *location = value;
  reconn_buffer_finalize_push(self, RECONN_VALUE_S32, sizeof(value));
}

void reconn_buffer_push_s64(ReconnBuffer *self, long long value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  long long *location = (long long *)&self->data[self->end];
  *location = value;
  reconn_buffer_finalize_push(self, RECONN_VALUE_S64, sizeof(value));
}

void reconn_buffer_push_f32(ReconnBuffer *self, float value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  float *location = (float *)&self->data[self->end];
  *location = value;

  reconn_buffer_finalize_push(self, RECONN_VALUE_F32, sizeof(value));
};

void reconn_buffer_push_f64(ReconnBuffer *self, double value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  double *location = (double *)&self->data[self->end];
  *location = value;

  reconn_buffer_finalize_push(self, RECONN_VALUE_F64, sizeof(value));
};

void reconn_buffer_push_cstring(ReconnBuffer *self, const char *value) {
  unsigned short length = strlen(value) + 1;
  reconn_buffer_grow_for(self, self->count, length);
  char *location = (char *)&self->data[self->end];
  memcpy(location, value, length);

  reconn_buffer_finalize_push(self, RECONN_VALUE_C_STRING, length);
}

void reconn_buffer_push_string(ReconnBuffer *self, const char *value,
                               unsigned short length) {
  reconn_buffer_grow_for(self, self->count, length);
  char *location = (char *)&self->data[self->end];
  memcpy(location, value, length);

  reconn_buffer_finalize_push(self, RECONN_VALUE_BYTE_STRING, length);
}

void reconn_buffer_push_wordp(ReconnBuffer *self, unsigned long value) {
  reconn_buffer_grow_for(self, self->count, sizeof(value));
  unsigned long *location = (unsigned long *)&self->data[self->end];
  *location = value;
  reconn_buffer_finalize_push(self, RECONN_VALUE_WORD_POINTER, sizeof(value));
}

/*
=============
GETTING ITEMS
=============
*/

void *reconn_buffer_get_void(ReconnBuffer *self, size_t index) {
  unsigned char start = self->items[index].start;
  void *location = (void *)&self->data[start];
  return location;
}

unsigned char reconn_buffer_get_u8(ReconnBuffer *self, size_t index) {
  unsigned char *location =
      (unsigned char *)reconn_buffer_get_void(self, index);
  return *location & UCHAR_MAX;
}

unsigned short reconn_buffer_get_u16(ReconnBuffer *self, size_t index) {
  unsigned short *location =
      (unsigned short *)reconn_buffer_get_void(self, index);
  return *location & USHRT_MAX;
}

unsigned long reconn_buffer_get_32(ReconnBuffer *self, size_t index) {
  unsigned long *location =
      (unsigned long *)reconn_buffer_get_void(self, index);
  return *location & ULONG_MAX;
}

unsigned long long reconn_buffer_get_u64(ReconnBuffer *self, size_t index) {
  unsigned long long *location =
      (unsigned long long *)reconn_buffer_get_void(self, index);
  return *location & ULLONG_MAX;
}

char reconn_buffer_get_s8(ReconnBuffer *self, size_t index) {
  char *location = (char *)reconn_buffer_get_void(self, index);
  return *location & UCHAR_MAX;
}

short reconn_buffer_get_s16(ReconnBuffer *self, size_t index) {
  short *location = (short *)reconn_buffer_get_void(self, index);
  return *location & USHRT_MAX;
}

long reconn_buffer_get_s32(ReconnBuffer *self, size_t index) {
  long *location = (long *)reconn_buffer_get_void(self, index);
  return *location & ULONG_MAX;
}

long long reconn_buffer_get_s64(ReconnBuffer *self, size_t index) {
  long long *location = (long long *)reconn_buffer_get_void(self, index);
  return *location & ULLONG_MAX;
}

float reconn_buffer_get_f32(ReconnBuffer *self, size_t index) {
  float *location = (float *)reconn_buffer_get_void(self, index);
  return *location;
}

double reconn_buffer_get_f64(ReconnBuffer *self, size_t index) {
  double *location = (double *)reconn_buffer_get_void(self, index);
  return *location;
}

char *reconn_buffer_get_cstring(ReconnBuffer *self, size_t index) {
  unsigned char start = self->items[index].start;
  unsigned short size = self->items[index].stop - self->items[index].start;
  char *location = (char *)&self->data[start];
  char *result = malloc(size);
  memcpy(result, location, size);
  return result;
}

char *reconn_buffer_get_string(ReconnBuffer *self, size_t index) {
  unsigned char start = self->items[index].start;
  unsigned short size = self->items[index].stop - self->items[index].start;
  char *location = (char *)&self->data[start];
  char *result = malloc(size);
  memcpy(result, location, size);
  return result;
}

unsigned long reconn_buffer_get_wordp(ReconnBuffer *self, size_t index) {
  unsigned long *location =
      (unsigned long *)reconn_buffer_get_void(self, index);
  return *location & ULONG_MAX;
}

/*
=============
POPPING ITEMS
=============
*/

void *reconn_buffer_pop_void(ReconnBuffer *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned short size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;

  void *location = (void *)&self->data[start];

  self->end -= size;
  self->count -= 1;

  return location;
}

unsigned char reconn_buffer_pop_u8(ReconnBuffer *self) {
  unsigned char *location = (unsigned char *)reconn_buffer_pop_void(self);
  return *location & UCHAR_MAX;
}

unsigned short reconn_buffer_pop_u16(ReconnBuffer *self) {
  unsigned short *location = (unsigned short *)reconn_buffer_pop_void(self);
  return *location & USHRT_MAX;
}

unsigned long reconn_buffer_pop_u32(ReconnBuffer *self) {
  unsigned long *location = (unsigned long *)reconn_buffer_pop_void(self);
  return *location & ULONG_MAX;
}

unsigned long long reconn_buffer_pop_u64(ReconnBuffer *self) {
  unsigned long long *location =
      (unsigned long long *)reconn_buffer_pop_void(self);
  return *location & ULLONG_MAX;
}

char reconn_buffer_pop_s8(ReconnBuffer *self) {
  char *location = (char *)reconn_buffer_pop_void(self);
  return *location & UCHAR_MAX;
}

short reconn_buffer_pop_s16(ReconnBuffer *self) {
  short *location = (short *)reconn_buffer_pop_void(self);

  return *location & USHRT_MAX;
}

long reconn_buffer_pop_s32(ReconnBuffer *self) {
  long *location = (long *)reconn_buffer_pop_void(self);
  return *location & ULONG_MAX;
}

long long reconn_buffer_pop_s64(ReconnBuffer *self) {
  long long *location = (long long *)reconn_buffer_pop_void(self);
  return *location & ULLONG_MAX;
}

float reconn_buffer_pop_f32(ReconnBuffer *self) {
  float *location = (float *)reconn_buffer_pop_void(self);
  return *location;
}

double reconn_buffer_pop_f64(ReconnBuffer *self) {
  double *location = (double *)reconn_buffer_pop_void(self);
  return *location;
}

char *reconn_buffer_pop_cstring(ReconnBuffer *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned short size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  char *location = (char *)&self->data[start];

  self->end -= size;
  self->count -= 1;

  char *result = malloc(size);
  memcpy(result, location, size);
  return result;
}

char *reconn_buffer_pop_string(ReconnBuffer *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned short size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  double *location = (double *)&self->data[start];

  self->end -= size;
  self->count -= 1;

  char *result = malloc(size);
  memcpy(result, location, size);
  return result;
}

unsigned long reconn_buffer_pop_wordp(ReconnBuffer *self) {
  unsigned long *location = (unsigned long *)reconn_buffer_pop_void(self);
  return *location & ULONG_MAX;
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