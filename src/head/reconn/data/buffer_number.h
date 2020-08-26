#ifndef RECONN_DATA_BUFFER_NUMBER_H
#define RECONN_DATA_BUFFER_NUMBER_H

#include "buffer.h"
#include "number.h"
#include "value.h"

/*
=============
PUSHING ITEMS
=============
*/

void reconn_buffer_push_number(ReconnBuffer *self, ReconnNumber value) {
  reconn_buffer_push_void(self, &value, sizeof(value), RECONN_VALUE_RCN_NUMBER);
}

/*
=============
GETTING ITEMS
=============
*/

ReconnNumber reconn_buffer_get_number(ReconnBuffer *self, size_t index) {
  return *(ReconnNumber *)reconn_buffer_get_void(self, index);
}

/*
=============
POPPING ITEMS
=============
*/

ReconnNumber reconn_buffer_pop_number(ReconnBuffer *self) {
  return *(ReconnNumber *)reconn_buffer_pop_void(self);
}

#endif