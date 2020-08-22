#ifndef RECONN_STACK_STACK_H
#define RECONN_STACK_STACK_H

#include <limits.h>
#include <stdio.h>
#include <string.h>

typedef enum ReconnStackItemKind {

  RECONN_STACK_ITEM_VOID,
  RECONN_STACK_ITEM_EMPTY,
  RECONN_STACK_ITEM_U8,
  RECONN_STACK_ITEM_U16,
  RECONN_STACK_ITEM_U32,
  RECONN_STACK_ITEM_U64,
  RECONN_STACK_ITEM_S8,
  RECONN_STACK_ITEM_S16,
  RECONN_STACK_ITEM_S32,
  RECONN_STACK_ITEM_S64,
  RECONN_STACK_ITEM_F32,
  RECONN_STACK_ITEM_F64,
  RECONN_STACK_ITEM_BYTE_STRING,
  RECONN_STACK_ITEM_C_STRING,

} ReconnStackItemKind;

typedef struct ReconnStackItem {
  ReconnStackItemKind kind;
  unsigned short start;
  unsigned short stop;
} ReconnStackItem;

typedef struct ReconnStack {
  unsigned short top;
  unsigned char count;
  unsigned char data[65536];
  ReconnStackItem items[256];
} ReconnStack;

ReconnStack reconn_makeStack() {
  ReconnStack self;
  self.top = 0;
  self.count = 0;
  return self;
}

void reconn_stack_print(ReconnStack *self) {
  printf("======\nTOP:%i\n", self->top);
  for (unsigned int i = 0; i < self->count; i++) {
    printf("(%5i:%5i)\n", self->items[i].start, self->items[i].stop);
    for (unsigned int si = self->items[i].start; si < self->items[i].stop;
         si++) {
      const unsigned char data = self->data[si];
      printf("(%3i:%5i) %02x (%3i)[%c]\n", i, si, data, data, data);
    }
    printf("---\n");
  }
}

/*
=========
ADD ITEMS
=========
*/

static void reconn_stack_finalize_push(ReconnStack *self,
                                       ReconnStackItemKind kind,
                                       unsigned short size) {
  self->items[self->count].kind = kind;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + size;

  self->top += size;
  self->count += 1;
}

void reconn_stack_push_u8(ReconnStack *self, unsigned char value) {
  unsigned char *location = (unsigned char *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_U8, sizeof(value));
};

void reconn_stack_push_u16(ReconnStack *self, unsigned short value) {
  unsigned short *location = (unsigned short *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_U16, sizeof(value));
};

void reconn_stack_push_u32(ReconnStack *self, unsigned long value) {
  unsigned long *location = (unsigned long *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_U32, sizeof(value));
};

void reconn_stack_push_u64(ReconnStack *self, unsigned long long value) {
  unsigned long long *location = (unsigned long long *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_U64, sizeof(value));
};

void reconn_stack_push_s8(ReconnStack *self, char value) {
  char *location = (char *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_S8, sizeof(value));
};

void reconn_stack_push_s16(ReconnStack *self, short value) {
  short *location = (short *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_S16, sizeof(value));
};

void reconn_stack_push_s32(ReconnStack *self, long value) {
  long *location = (long *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_S32, sizeof(value));
};

void reconn_stack_push_s64(ReconnStack *self, long long value) {
  long long *location = (long long *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_S64, sizeof(value));
};

void reconn_stack_push_f32(ReconnStack *self, float value) {
  float *location = (float *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_F32, sizeof(value));
};

void reconn_stack_push_f64(ReconnStack *self, double value) {
  double *location = (double *)&self->data[self->top];
  *location = value;

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_F64, sizeof(value));
};

void reconn_stack_push_cstring(ReconnStack *self, char *value) {
  unsigned short length = strlen(value) + 1;
  char *location = (char *)&self->data[self->top];
  memcpy(location, value, length);

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_C_STRING, length);
}

void reconn_stack_push_string(ReconnStack *self, char *value,
                              unsigned short length) {
  char *location = (char *)&self->data[self->top];
  memcpy(location, value, length);

  reconn_stack_finalize_push(self, RECONN_STACK_ITEM_BYTE_STRING, length);
}

/*
============
REMOVE ITEMS
============
*/

void *reconn_stack_pop_void(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned short size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;

  void *location = (void *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return location;
}

unsigned char reconn_stack_pop_u8(ReconnStack *self) {
  unsigned char *location = (unsigned char *)reconn_stack_pop_void(self);
  return *location & UCHAR_MAX;
}

unsigned short reconn_stack_pop_u16(ReconnStack *self) {
  unsigned short *location = (unsigned short *)reconn_stack_pop_void(self);
  return *location & USHRT_MAX;
}

unsigned long reconn_stack_pop_u32(ReconnStack *self) {
  unsigned long *location = (unsigned long *)reconn_stack_pop_void(self);
  return *location & ULONG_MAX;
}

unsigned long long reconn_stack_pop_u64(ReconnStack *self) {
  unsigned long long *location =
      (unsigned long long *)reconn_stack_pop_void(self);
  return *location & ULLONG_MAX;
}

char reconn_stack_pop_s8(ReconnStack *self) {
  char *location = (char *)reconn_stack_pop_void(self);
  return *location & UCHAR_MAX;
}

short reconn_stack_pop_s16(ReconnStack *self) {
  short *location = (short *)reconn_stack_pop_void(self);

  return *location & USHRT_MAX;
}

long reconn_stack_pop_s32(ReconnStack *self) {
  long *location = (long *)reconn_stack_pop_void(self);
  return *location & ULONG_MAX;
}

long long reconn_stack_pop_s64(ReconnStack *self) {
  long long *location = (long long *)reconn_stack_pop_void(self);
  return *location & ULLONG_MAX;
}

float reconn_stack_pop_f32(ReconnStack *self) {
  float *location = (float *)reconn_stack_pop_void(self);
  return *location;
}

double reconn_stack_pop_f64(ReconnStack *self) {
  double *location = (double *)reconn_stack_pop_void(self);
  return *location;
}

void reconn_stack_pop_cstring(ReconnStack *self, char *dest) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned short size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  char *location = (char *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  memcpy(dest, location, size);
}

void reconn_stack_pop_string(ReconnStack *self, char *dest) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned short size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  double *location = (double *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  memcpy(dest, location, size);
}

/*
==================
UTILLITY FUNCTIONS
==================
*/

unsigned char reconn_stack_size(ReconnStack *self) { return self->count; }
ReconnStackItemKind reconn_stack_kind_at(ReconnStack *self,
                                         unsigned char index) {
  return self->items[index].kind;
}

#endif
