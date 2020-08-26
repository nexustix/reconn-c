#ifndef RECONN_DATA_BUFFER_FLOAT_H
#define RECONN_DATA_BUFFER_FLOAT_H

#include "buffer.h"
#include "value.h"
//#include "limits.h"

/*
=============
PUSHING ITEMS
=============
*/

void reconn_buffer_push_f32(ReconnBuffer *self, float value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_F32);
}

void reconn_buffer_push_f64(ReconnBuffer *self, double value) {
  // reconn_buffer_grow_for(self, self->count, sizeof(value));
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_F64);
}

/*
=============
GETTING ITEMS
=============
*/

float reconn_buffer_get_f32(ReconnBuffer *self, size_t index) {
  return *(float *)reconn_buffer_get_void(self, index);
}

double reconn_buffer_get_f64(ReconnBuffer *self, size_t index) {
  return *(double *)reconn_buffer_get_void(self, index);
}

/*
=============
POPPING ITEMS
=============
*/

float reconn_buffer_pop_f32(ReconnBuffer *self) {
  return *(float *)reconn_buffer_pop_void(self);
}
double reconn_buffer_pop_f64(ReconnBuffer *self) {
  return *(double *)reconn_buffer_pop_void(self);
}

#endif