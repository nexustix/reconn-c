#ifndef RECONN_STACK_STACK_H
#define RECONN_STACK_STACK_H

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
  printf("TOP:%i\n", self->top);
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

void reconn_stack_push_u8(ReconnStack *self, unsigned char value) {
  unsigned char *location = (unsigned char *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_U8;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_u16(ReconnStack *self, unsigned short value) {
  unsigned short *location = (unsigned short *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_U16;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_u32(ReconnStack *self, unsigned long value) {
  unsigned long *location = (unsigned long *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_U32;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_u64(ReconnStack *self, unsigned long long value) {
  unsigned long long *location = (unsigned long long *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_U64;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_s8(ReconnStack *self, char value) {
  char *location = (char *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_S8;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_s16(ReconnStack *self, short value) {
  short *location = (short *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_S16;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_s32(ReconnStack *self, long value) {
  long *location = (long *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_S32;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_s64(ReconnStack *self, long long value) {
  long long *location = (long long *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_S64;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_f32(ReconnStack *self, float value) {
  float *location = (float *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_F32;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_f64(ReconnStack *self, double value) {
  double *location = (double *)&self->data[self->top];
  *location = value;

  self->items[self->count].kind = RECONN_STACK_ITEM_F64;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + sizeof(value);

  self->top += sizeof(value);
  self->count += 1;
};

void reconn_stack_push_cstring(ReconnStack *self, char *value) {
  unsigned short length = strlen(value) + 1;
  char *location = (char *)&self->data[self->top];
  memcpy(location, value, length);

  self->items[self->count].kind = RECONN_STACK_ITEM_C_STRING;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + length;

  self->top += length;
  self->count += 1;
}

void reconn_stack_push_string(ReconnStack *self, char *value,
                              unsigned short length) {

  char *location = (char *)&self->data[self->top];
  memcpy(location, value, length);

  self->items[self->count].kind = RECONN_STACK_ITEM_BYTE_STRING;
  self->items[self->count].start = self->top;
  self->items[self->count].stop = self->top + length;

  self->top += length;
  self->count += 1;
}

/*
============
REMOVE ITEMS
============
*/

unsigned char reconn_stack_pop_u8(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  unsigned char *location = (unsigned char *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location & 0xff;
}

unsigned short reconn_stack_pop_u16(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  unsigned short *location = (unsigned short *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location & 0xffff;
}

unsigned long reconn_stack_pop_u32(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  unsigned long *location = (unsigned long *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location & 0xffffffff;
}

unsigned long long reconn_stack_pop_u64(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  unsigned long long *location = (unsigned long long *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location & 0xffffffffffffffff;
}

char reconn_stack_pop_s8(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  char *location = (char *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location & 0xff;
}

short reconn_stack_pop_s16(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  short *location = (short *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location & 0xffff;
}

long reconn_stack_pop_s32(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  long *location = (long *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location & 0xffffffff;
}

long long reconn_stack_pop_s64(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  long long *location = (long long *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location & 0xffffffffffffffff;
}

float reconn_stack_pop_f32(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  float *location = (float *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location;
}

double reconn_stack_pop_f64(ReconnStack *self) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  double *location = (double *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  return *location;
}

void reconn_stack_pop_cstring(ReconnStack *self, char *dest) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
      self->items[self->count - 1].stop - self->items[self->count - 1].start;
  char *location = (char *)&self->data[start];

  self->top -= size;
  self->count -= 1;

  memcpy(dest, location, size);
}

void reconn_stack_pop_string(ReconnStack *self, char *dest) {
  unsigned char start = self->items[self->count - 1].start;
  unsigned char size =
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
