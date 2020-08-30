#ifndef RECONN_VALUE_H
#define RECONN_VALUE_H

#include <stdio.h>
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
  RECONN_VALUE_WORD_SECONDARY,
  RECONN_VALUE_WORD_COMPILE,
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

const char *reconn_value_kind_to_string(ReconnValueKind kind) {
  switch (kind) {
  case RECONN_VALUE_VOID:
    return "void";
    break;
  case RECONN_VALUE_EMPTY:
    return "empty";
    break;
  case RECONN_VALUE_UNDEFINED:
    return "undefined";
    break;
  case RECONN_VALUE_U8:
    return "u8";
    break;
  case RECONN_VALUE_U16:
    return "u16";
    break;
  case RECONN_VALUE_U32:
    return "u32";
    break;
  case RECONN_VALUE_U64:
    return "u64";
    break;
  case RECONN_VALUE_S8:
    return "s8";
    break;
  case RECONN_VALUE_S16:
    return "s16";
    break;
  case RECONN_VALUE_S32:
    return "s32";
    break;
  case RECONN_VALUE_S64:
    return "s64";
    break;
  case RECONN_VALUE_F32:
    return "f32";
    break;
  case RECONN_VALUE_F64:
    return "f64";
    break;
  case RECONN_VALUE_RCN_NUMBER:
    return "rcn_number";
    break;
  case RECONN_VALUE_BYTE_STRING:
    return "bstr";
    break;
  case RECONN_VALUE_C_STRING:
    return "cstr";
    break;
  case RECONN_VALUE_STRUCT:
    return "struct";
    break;
  case RECONN_VALUE_POINTER:
    return "pointer";
    break;
  case RECONN_VALUE_WORD_POINTER:
    return "wordref";
    break;
  case RECONN_VALUE_WORD_PRIMARY:
    return "word_primary";
    break;
  case RECONN_VALUE_WORD_SECONDARY:
    return "word_secondary";
    break;
  case RECONN_VALUE_WORD_COMPILE:
    return "word_compile";
    break;
  case RECONN_VALUE_WORD_BUFFER:
    return "wordbuffer";
    break;
  default:
    return "???";
    break;
  }
}

char *reconn_value_value_to_string(ReconnValueKind kind, const void *value) {

  char *str = (char *)malloc(32);

  switch (kind) {
  case RECONN_VALUE_VOID:
    sprintf(str, "N/A");
    break;
  case RECONN_VALUE_EMPTY:
    sprintf(str, "N/A");
    break;
  case RECONN_VALUE_UNDEFINED:
    sprintf(str, "???");
    break;
  case RECONN_VALUE_U8:
    sprintf(str, "%u", *(unsigned char *)value);
    break;
  case RECONN_VALUE_U16:
    sprintf(str, "%u", *(unsigned short *)value);
    break;
  case RECONN_VALUE_U32:
    sprintf(str, "%lu", *(unsigned long *)value);
    break;
  case RECONN_VALUE_U64:
    sprintf(str, "%llu", *(unsigned long long *)value);
    break;
  case RECONN_VALUE_S8:
    sprintf(str, "%i", *(char *)value);
    break;
  case RECONN_VALUE_S16:
    sprintf(str, "%i", *(short *)value);
    break;
  case RECONN_VALUE_S32:
    sprintf(str, "%li", *(long *)value);
    break;
  case RECONN_VALUE_S64:
    sprintf(str, "%lli", *(long long *)value);
    break;
  case RECONN_VALUE_F32:
    sprintf(str, "%f", *(float *)value);
    break;
  case RECONN_VALUE_F64:
    sprintf(str, "%lf", *(double *)value);
    break;
  case RECONN_VALUE_RCN_NUMBER:
    sprintf(str, "_");
    break;
  case RECONN_VALUE_BYTE_STRING:
    sprintf(str, "_");
    break;
  case RECONN_VALUE_C_STRING:
    sprintf(str, "%s", (char *)value);
    break;
  case RECONN_VALUE_STRUCT:
    sprintf(str, "_");
    break;
  case RECONN_VALUE_POINTER:
    sprintf(str, "%llu", (unsigned long long)value);
    break;
  case RECONN_VALUE_WORD_POINTER:
    sprintf(str, "_");
    break;
  case RECONN_VALUE_WORD_PRIMARY:
    sprintf(str, "_");
    break;
  case RECONN_VALUE_WORD_SECONDARY:
    sprintf(str, "_");
    break;
  case RECONN_VALUE_WORD_COMPILE:
    sprintf(str, "_");
    break;
  case RECONN_VALUE_WORD_BUFFER:
    sprintf(str, "_");
    break;
  default:
    sprintf(str, "???");
    break;
  }
  return str;
}

int reconn_value_is_true(ReconnValueKind kind, const void *value) {
  switch (kind) {
  case RECONN_VALUE_VOID:
    return 0;
    break;
  case RECONN_VALUE_EMPTY:
    return 0;
    break;
  case RECONN_VALUE_UNDEFINED:
    return -1;
    break;
  case RECONN_VALUE_U8:
    return *(unsigned char *)value;
    break;
  case RECONN_VALUE_U16:
    return *(unsigned short *)value;
    break;
  case RECONN_VALUE_U32:
    return *(unsigned long *)value;
    break;
  case RECONN_VALUE_U64:
    return *(unsigned long long *)value;
    break;
  case RECONN_VALUE_S8:
    return *(char *)value;
    break;
  case RECONN_VALUE_S16:
    return *(short *)value;
    break;
  case RECONN_VALUE_S32:
    return *(long *)value;
    break;
  case RECONN_VALUE_S64:
    return *(long long *)value;
    break;
  case RECONN_VALUE_F32:
    return *(float *)value;
    break;
  case RECONN_VALUE_F64:
    return *(double *)value;
    break;
  case RECONN_VALUE_RCN_NUMBER:
    // FIXME RCN NUMBERS WILL NEVER EVALUATE TO TRUE
    return 0;
    break;
  case RECONN_VALUE_BYTE_STRING:
    return !(((char *)value) == 0);
    break;
  case RECONN_VALUE_C_STRING:
    return !(((char *)value) == 0);
    break;
  case RECONN_VALUE_STRUCT:
    return 1;
    break;
  case RECONN_VALUE_POINTER:
    return !(value == NULL);
    break;
  case RECONN_VALUE_WORD_POINTER:
    return 1;
    break;
  case RECONN_VALUE_WORD_PRIMARY:
    return 1;
    break;
  case RECONN_VALUE_WORD_SECONDARY:
    return 1;
    break;
  case RECONN_VALUE_WORD_COMPILE:
    return 1;
    break;
  case RECONN_VALUE_WORD_BUFFER:
    return 1;
    break;
  default:
    return -1;
    break;
  }
}

ReconnValueKind reconn_value_find_compromise(ReconnValueKind kinda,
                                             ReconnValueKind kindb) {
  if (kinda == kindb) {
    return kinda;
  }

  switch (kinda) {
  case RECONN_VALUE_U8:
    switch (kindb) {
    case RECONN_VALUE_U16:
    case RECONN_VALUE_U32:
    case RECONN_VALUE_U64:
      return kindb;
      break;
    case RECONN_VALUE_S8:
      return RECONN_VALUE_S16;
      break;
    case RECONN_VALUE_S16:
    case RECONN_VALUE_S32:
    case RECONN_VALUE_S64:
    case RECONN_VALUE_F32:
    case RECONN_VALUE_F64:
      return kindb;
      break;
    default:
      break;
    }
    break;
  case RECONN_VALUE_U16:
    switch (kindb) {
    case RECONN_VALUE_U8:
      return RECONN_VALUE_U16;
      break;
    case RECONN_VALUE_U32:
    case RECONN_VALUE_U64:
      return kindb;
      break;
    case RECONN_VALUE_S8:
    case RECONN_VALUE_S16:
    case RECONN_VALUE_S32:
      return RECONN_VALUE_S32;
      break;
    case RECONN_VALUE_S64:
    case RECONN_VALUE_F32:
    case RECONN_VALUE_F64:
      return kindb;
      break;
    default:
      break;
    }
    break;
  case RECONN_VALUE_U32:
    switch (kindb) {
    case RECONN_VALUE_U8:
    case RECONN_VALUE_U16:
      return RECONN_VALUE_U32;
      break;
    case RECONN_VALUE_U64:
      return RECONN_VALUE_U64;
      break;
    case RECONN_VALUE_S8:
    case RECONN_VALUE_S16:
    case RECONN_VALUE_S32:
    case RECONN_VALUE_S64:
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_F32:
    case RECONN_VALUE_F64:
      return kindb;
      break;
    default:
      break;
    }
    break;
  case RECONN_VALUE_U64:
    switch (kindb) {
    case RECONN_VALUE_U8:
    case RECONN_VALUE_U16:
    case RECONN_VALUE_U32:
    case RECONN_VALUE_U64:
      return RECONN_VALUE_U64;
      break;
    case RECONN_VALUE_S8:
    case RECONN_VALUE_S16:
    case RECONN_VALUE_S32:
    case RECONN_VALUE_S64:
      // FIXME can lose data
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_F32:
    case RECONN_VALUE_F64:
      return kindb;
    default:
      break;
    }
    break;
  case RECONN_VALUE_S8:
    switch (kindb) {
    case RECONN_VALUE_U8:
      return RECONN_VALUE_S16;
      break;
    case RECONN_VALUE_U16:
      return RECONN_VALUE_S32;
      break;
    case RECONN_VALUE_U32:
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_U64:
      // FIXME can lose data
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_S16:
    case RECONN_VALUE_S32:
    case RECONN_VALUE_S64:
    case RECONN_VALUE_F32:
    case RECONN_VALUE_F64:
      return kindb;
      break;
    default:
      break;
    }
    break;
  case RECONN_VALUE_S16:
    switch (kindb) {
    case RECONN_VALUE_U8:
      return RECONN_VALUE_S16;
      break;
    case RECONN_VALUE_U16:
      return RECONN_VALUE_S32;
      break;
    case RECONN_VALUE_U32:
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_U64:
      // FIXME can lose data
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_S8:
      return RECONN_VALUE_S16;
      break;
    case RECONN_VALUE_S32:
    case RECONN_VALUE_S64:
    case RECONN_VALUE_F32:
    case RECONN_VALUE_F64:
      return kindb;
      break;
    default:
      break;
    }
    break;
  case RECONN_VALUE_S32:
    switch (kindb) {
    case RECONN_VALUE_U8:
      return RECONN_VALUE_S32;
      break;
    case RECONN_VALUE_U16:
      return RECONN_VALUE_S32;
      break;
    case RECONN_VALUE_U32:
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_U64:
      // FIXME can lose data
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_S8:
    case RECONN_VALUE_S16:
      return RECONN_VALUE_S32;
      break;
    case RECONN_VALUE_S64:
    case RECONN_VALUE_F32:
    case RECONN_VALUE_F64:
      return kindb;
      break;
    default:
      break;
    }
    break;
  case RECONN_VALUE_S64:
    switch (kindb) {
    case RECONN_VALUE_U8:
    case RECONN_VALUE_U16:
    case RECONN_VALUE_U32:
    case RECONN_VALUE_U64:
      // FIXME can lose data
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_S8:
    case RECONN_VALUE_S16:
    case RECONN_VALUE_S32:
      return RECONN_VALUE_S64;
      break;
    case RECONN_VALUE_F32:
    case RECONN_VALUE_F64:
      return kindb;
      break;
    default:
      break;
    }
    break;
  case RECONN_VALUE_F32:
    switch (kindb) {
    case RECONN_VALUE_U8:
    case RECONN_VALUE_U16:
    case RECONN_VALUE_U32:
    case RECONN_VALUE_U64:
    case RECONN_VALUE_S8:
    case RECONN_VALUE_S16:
    case RECONN_VALUE_S32:
    case RECONN_VALUE_S64:
      return RECONN_VALUE_F32;
      break;
    case RECONN_VALUE_F64:
      return RECONN_VALUE_F64;
      break;
    default:
      break;
    }
    break;
  case RECONN_VALUE_F64:
    switch (kindb) {
    case RECONN_VALUE_U8:
    case RECONN_VALUE_U16:
    case RECONN_VALUE_U32:
    case RECONN_VALUE_U64:
    case RECONN_VALUE_S8:
    case RECONN_VALUE_S16:
    case RECONN_VALUE_S32:
    case RECONN_VALUE_S64:
    case RECONN_VALUE_F32:
      return RECONN_VALUE_F64;
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
  return RECONN_VALUE_VOID;
}

int reconn_value_is_number(ReconnValueKind kind) {
  switch (kind) {
  case RECONN_VALUE_U8:
  case RECONN_VALUE_U16:
  case RECONN_VALUE_U32:
  case RECONN_VALUE_U64:
  case RECONN_VALUE_S8:
  case RECONN_VALUE_S16:
  case RECONN_VALUE_S32:
  case RECONN_VALUE_S64:
  case RECONN_VALUE_F32:
  case RECONN_VALUE_F64:
    return 1;
    break;
  default:
    return 0;
    break;
  }
}

int reconn_value_is_signed(ReconnValueKind kind) {
  switch (kind) {
  case RECONN_VALUE_S8:
  case RECONN_VALUE_S16:
  case RECONN_VALUE_S32:
  case RECONN_VALUE_S64:
    return 1;
    break;
  case RECONN_VALUE_U8:
  case RECONN_VALUE_U16:
  case RECONN_VALUE_U32:
  case RECONN_VALUE_U64:
  case RECONN_VALUE_F32:
  case RECONN_VALUE_F64:
  default:
    return 0;
    break;
  }
}

int reconn_value_is_float(ReconnValueKind kind) {
  switch (kind) {
  case RECONN_VALUE_F32:
  case RECONN_VALUE_F64:
    return 1;
    break;
  case RECONN_VALUE_U8:
  case RECONN_VALUE_U16:
  case RECONN_VALUE_U32:
  case RECONN_VALUE_U64:
  case RECONN_VALUE_S8:
  case RECONN_VALUE_S16:
  case RECONN_VALUE_S32:
  case RECONN_VALUE_S64:
  default:
    return 0;
    break;
  }
}

unsigned long long reconn_value_to_u64(ReconnValueKind kind,
                                       const void *value) {
  switch (kind) {
  case RECONN_VALUE_U8:
    return (unsigned long long)*(unsigned char *)value;
    break;
  case RECONN_VALUE_U16:
    return (unsigned long long)*(unsigned short *)value;
    break;
  case RECONN_VALUE_U32:
    return (unsigned long long)*(unsigned long *)value;
    break;
  case RECONN_VALUE_U64:
    return (unsigned long long)*(unsigned long long *)value;
    break;
  case RECONN_VALUE_S8:
    return (unsigned long long)*(char *)value;
    break;
  case RECONN_VALUE_S16:
    return (unsigned long long)*(short *)value;
    break;
  case RECONN_VALUE_S32:
    return (unsigned long long)*(long *)value;
    break;
  case RECONN_VALUE_S64:
    return (unsigned long long)*(long long *)value;
    break;
  case RECONN_VALUE_F32:
    return (unsigned long long)*(float *)value;
    break;
  case RECONN_VALUE_F64:
    return (unsigned long long)*(double *)value;
    break;
  default:
    return 0;
    break;
  }
}
long long reconn_value_to_s64(ReconnValueKind kind, const void *value) {
  switch (kind) {
  case RECONN_VALUE_U8:
    return (long long)*(unsigned char *)value;
    break;
  case RECONN_VALUE_U16:
    return (long long)*(unsigned short *)value;
    break;
  case RECONN_VALUE_U32:
    return (long long)*(unsigned long *)value;
    break;
  case RECONN_VALUE_U64:
    return (long long)*(unsigned long long *)value;
    break;
  case RECONN_VALUE_S8:
    return (long long)*(char *)value;
    break;
  case RECONN_VALUE_S16:
    return (long long)*(short *)value;
    break;
  case RECONN_VALUE_S32:
    return (long long)*(long *)value;
    break;
  case RECONN_VALUE_S64:
    return (long long)*(long long *)value;
    break;
  case RECONN_VALUE_F32:
    return (long long)*(float *)value;
    break;
  case RECONN_VALUE_F64:
    return (long long)*(double *)value;
    break;
  default:
    return 0;
    break;
  }
}
double reconn_value_to_f64(ReconnValueKind kind, const void *value) {
  switch (kind) {
  case RECONN_VALUE_U8:
    return (double)*(unsigned char *)value;
    break;
  case RECONN_VALUE_U16:
    return (double)*(unsigned short *)value;
    break;
  case RECONN_VALUE_U32:
    return (double)*(unsigned long *)value;
    break;
  case RECONN_VALUE_U64:
    return (double)*(unsigned long long *)value;
    break;
  case RECONN_VALUE_S8:
    return (double)*(char *)value;
    break;
  case RECONN_VALUE_S16:
    return (double)*(short *)value;
    break;
  case RECONN_VALUE_S32:
    return (double)*(long *)value;
    break;
  case RECONN_VALUE_S64:
    return (double)*(long long *)value;
    break;
  case RECONN_VALUE_F32:
    return (double)*(float *)value;
    break;
  case RECONN_VALUE_F64:
    return (double)*(double *)value;
    break;
  default:
    return 0;
    break;
  }
}

#endif