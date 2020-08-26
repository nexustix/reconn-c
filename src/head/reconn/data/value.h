#ifndef RECONN_VALUE_H
#define RECONN_VALUE_H

#include <stdlib.h>

typedef enum ReconnValueKind {

  RECONN_VALUE_VOID,
  RECONN_VALUE_EMPTY,
  RECONN_VALUE_UNDEFINED,
  RECONN_VALUE_U8,
  RECONN_VALUE_U16,
  RECONN_VALUE_U32,
  RECONN_VALUE_U64,
  RECONN_VALUE_S8,
  RECONN_VALUE_S16,
  RECONN_VALUE_S32,
  RECONN_VALUE_S64,
  RECONN_VALUE_F32,
  RECONN_VALUE_F64,
  RECONN_VALUE_RCN_NUMBER,
  RECONN_VALUE_BYTE_STRING,
  RECONN_VALUE_C_STRING,
  RECONN_VALUE_STRUCT,
  RECONN_VALUE_POINTER,
  RECONN_VALUE_WORD_POINTER,
  RECONN_VALUE_WORD_PRIMARY,
  RECONN_VALUE_WORD_BUFFER,

} ReconnValueKind;

typedef struct ReconnValue {
  ReconnValueKind kind;
  size_t reserve;
  // unsigned long count;
  // extra data here;

} ReconnValue;

void *reconn_value_allot(ReconnValueKind kind, size_t size) {
  ReconnValue *outer_pointer =
      (ReconnValue *)calloc(1, sizeof(ReconnValue) + size);

  outer_pointer->kind = RECONN_VALUE_UNDEFINED;
  outer_pointer->reserve = size;

  void *inner_pointer = outer_pointer + sizeof(ReconnValue);
  return inner_pointer;
}

void reconn_value_free(void *inner_pointer) {
  void *outer_pointer = inner_pointer - sizeof(ReconnValue);
  free(outer_pointer);
}

void *reconn_value_resizemin(void *inner_pointer, size_t minsize) {
  ReconnValue *outer_pointer =
      (ReconnValue *)inner_pointer - sizeof(ReconnValue);

  if (outer_pointer->reserve < minsize) {
    outer_pointer =
        (ReconnValue *)realloc(outer_pointer, sizeof(ReconnValue) + minsize);
    void *new_inner_pointer = outer_pointer + sizeof(ReconnValue);
    outer_pointer->reserve = minsize;
    return new_inner_pointer;
  }
  return inner_pointer;
}

size_t reconn_value_get_size(void *inner_pointer) {
  ReconnValue *outer_pointer =
      (ReconnValue *)inner_pointer - sizeof(ReconnValue);
  return outer_pointer->reserve;
}

#endif