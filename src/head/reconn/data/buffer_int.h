#ifndef RECONN_DATA_BUFFER_INT_H
#define RECONN_DATA_BUFFER_INT_H

#include "buffer.h"
#include "limits.h"
#include "value.h"
//#include <stdlib.h>

/*
=============
PUSHING ITEMS
=============
*/

void reconn_buffer_push_u8(ReconnBuffer *self, unsigned char value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_U8);
}

void reconn_buffer_push_u16(ReconnBuffer *self, unsigned short value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_U16);
}

void reconn_buffer_push_u32(ReconnBuffer *self, unsigned long value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_U32);
}

void reconn_buffer_push_u64(ReconnBuffer *self, unsigned long long value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_U64);
}

void reconn_buffer_push_s8(ReconnBuffer *self, char value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_S8);
}

void reconn_buffer_push_s16(ReconnBuffer *self, short value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_S16);
}

void reconn_buffer_push_s32(ReconnBuffer *self, long value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_S32);
}

void reconn_buffer_push_s64(ReconnBuffer *self, long long value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_S64);
}

/*
=============
GETTING ITEMS
=============
*/

unsigned char reconn_buffer_get_u8(ReconnBuffer *self, size_t index) {
  return *((unsigned char *)reconn_buffer_get_void(self, index)) & UCHAR_MAX;
}

unsigned short reconn_buffer_get_u16(ReconnBuffer *self, size_t index) {
  return *((unsigned short *)reconn_buffer_get_void(self, index)) & USHRT_MAX;
}

unsigned long reconn_buffer_get_u32(ReconnBuffer *self, size_t index) {
  return *((unsigned long *)reconn_buffer_get_void(self, index)) & ULONG_MAX;
}

unsigned long long reconn_buffer_get_u64(ReconnBuffer *self, size_t index) {
  return *((unsigned long long *)reconn_buffer_get_void(self, index)) &
         ULLONG_MAX;
}

char reconn_buffer_get_s8(ReconnBuffer *self, size_t index) {
  return *((char *)reconn_buffer_get_void(self, index)) & UCHAR_MAX;
}

short reconn_buffer_get_s16(ReconnBuffer *self, size_t index) {
  return *((short *)reconn_buffer_get_void(self, index)) & USHRT_MAX;
}

long reconn_buffer_get_s32(ReconnBuffer *self, size_t index) {
  return *((long *)reconn_buffer_get_void(self, index)) & ULONG_MAX;
}

long long reconn_buffer_get_s64(ReconnBuffer *self, size_t index) {
  return *((long long *)reconn_buffer_get_void(self, index)) & ULLONG_MAX;
}

/*
=============
POPPING ITEMS
=============
*/

unsigned char reconn_buffer_pop_u8(ReconnBuffer *self) {
  return *((unsigned char *)reconn_buffer_pop_void(self)) & UCHAR_MAX;
}
unsigned short reconn_buffer_pop_u16(ReconnBuffer *self) {
  return *((unsigned short *)reconn_buffer_pop_void(self)) & USHRT_MAX;
}
unsigned long reconn_buffer_pop_u32(ReconnBuffer *self) {
  return *((unsigned long *)reconn_buffer_pop_void(self)) & ULONG_MAX;
}
unsigned long long reconn_buffer_pop_u64(ReconnBuffer *self) {
  return *((unsigned long long *)reconn_buffer_pop_void(self)) & ULLONG_MAX;
}

char reconn_buffer_pop_s8(ReconnBuffer *self) {
  return *((char *)reconn_buffer_pop_void(self)) & UCHAR_MAX;
}
short reconn_buffer_pop_s16(ReconnBuffer *self) {
  return *((short *)reconn_buffer_pop_void(self)) & USHRT_MAX;
}
long reconn_buffer_pop_s32(ReconnBuffer *self) {
  return *((long *)reconn_buffer_pop_void(self)) & ULONG_MAX;
}
long long reconn_buffer_pop_s64(ReconnBuffer *self) {
  return *((long long *)reconn_buffer_pop_void(self)) & ULLONG_MAX;
}

#endif