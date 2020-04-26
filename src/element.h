#ifndef ELEMENT_H
#define ELEMENT_H

//#include "vm.h"
#include <assert.h>
#include <stdlib.h>

#include "util.h"

//#include "bignum.h"
//#include "list.h"
//#include "dictionary.h"
//#include "vm.h"

typedef enum {
  /*00*/ ELEMENT_VOID,   // uninitialized
  /*01*/ ELEMENT_EMPTY,  // ready for contents
  /*02*/ ELEMENT_BIGNUM,
  /*03*/ ELEMENT_I8,
  /*04*/ ELEMENT_I16,
  /*05*/ ELEMENT_I32,
  /*06*/ ELEMENT_U8,
  /*07*/ ELEMENT_U16,
  /*08*/ ELEMENT_U32,
  /*09*/ ELEMENT_WORD_PRIMARY,
  /*10*/ ELEMENT_WORD_SECONDARY,
  /*11*/ ELEMENT_ENUM,
  /*12*/ ELEMENT_CSTRING,
} ElementKind;

typedef struct Element {
  ElementKind kind;
  void* data;
  // Bignum data;
  // unsigned int size;
  char* id;
} Element;

Element* newElement() {
  Element* self = (Element*)calloc(1, sizeof(*self));
  self->data = NULL;
  self->id = NULL;
  self->kind = ELEMENT_EMPTY;
  return self;
}

/*
Bignum* element_get_bignum(Element* self) { return (Bignum*)self->data; }

Element* element_set_bignum(Element* destination, Bignum* source) {
  destination->data = (void*)source;
  destination->kind = ELEMENT_BIGNUM;
  return destination;
}
*/

int* element_get_enum(Element* self) { return (int*)self->data; }

Element* element_set_enum(Element* destination, int* source) {
  destination->data = (void*)source;
  destination->kind = ELEMENT_ENUM;
  return destination;
}

const char* element_get_cstring(Element* self) {
  return (const char*)self->data;
}

Element* element_set_cstring(Element* destination, const char* source) {
  destination->data = (void*)source;
  destination->kind = ELEMENT_CSTRING;
  return destination;
}

// functions for giving ints

void element_set_i8(Element* self, char* value) {
  // self->data = realloc(self->data, sizeof(char*));
  self->kind = ELEMENT_I8;
  self->data = value;
}
void element_set_i16(Element* self, short* value) {
  self->kind = ELEMENT_I16;
  self->data = value;
}
void element_set_i32(Element* self, long* value) {
  self->kind = ELEMENT_I32;
  self->data = value;
}
void element_set_u8(Element* self, unsigned char* value) {
  self->kind = ELEMENT_U8;
  self->data = value;
}
void element_set_u16(Element* self, unsigned short* value) {
  self->kind = ELEMENT_U16;
  self->data = value;
}
void element_set_u32(Element* self, unsigned long* value) {
  self->kind = ELEMENT_U32;
  self->data = value;
}

// Functions for taking ints

char element_take_i8(Element* self, int cleanup) {
  char r = 0;
  switch (self->kind) {
    case ELEMENT_I8:
      r = (char)*(char*)self->data;
      break;
    case ELEMENT_I16:
      r = (char)*(short*)self->data;
      break;
    case ELEMENT_I32:
      r = (char)*(long*)self->data;
      break;
    case ELEMENT_U8:
      r = (char)*(unsigned char*)self->data;
      break;
    case ELEMENT_U16:
      r = (char)*(unsigned short*)self->data;
      break;
    case ELEMENT_U32:
      r = (char)*(unsigned long*)self->data;
      break;

    default:
      error(0, "unable to take i8");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

short element_take_i16(Element* self, int cleanup) {
  short r = 0;
  switch (self->kind) {
    case ELEMENT_I8:
      r = (short)*(char*)self->data;
      break;
    case ELEMENT_I16:
      r = (short)*(short*)self->data;
      break;
    case ELEMENT_I32:
      r = (short)*(long*)self->data;
      break;
    case ELEMENT_U8:
      r = (short)*(unsigned char*)self->data;
      break;
    case ELEMENT_U16:
      r = (short)*(unsigned short*)self->data;
      break;
    case ELEMENT_U32:
      r = (short)*(unsigned long*)self->data;
      break;

    default:
      error(0, "unable to take i16");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

long element_take_i32(Element* self, int cleanup) {
  long r = 0;
  switch (self->kind) {
    case ELEMENT_I8:
      r = (long)*(char*)self->data;
      break;
    case ELEMENT_I16:
      r = (long)*(short*)self->data;
      break;
    case ELEMENT_I32:
      r = (long)*(long*)self->data;
      break;
    case ELEMENT_U8:
      r = (long)*(unsigned char*)self->data;
      break;
    case ELEMENT_U16:
      r = (long)*(unsigned short*)self->data;
      break;
    case ELEMENT_U32:
      r = (long)*(unsigned long*)self->data;
      break;

    default:
      error(0, "unable to take i32");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

unsigned char element_take_u8(Element* self, int cleanup) {
  unsigned char r = 0;
  switch (self->kind) {
    case ELEMENT_I8:
      r = (unsigned char)*(char*)self->data;
      break;
    case ELEMENT_I16:
      r = (unsigned char)*(short*)self->data;
      break;
    case ELEMENT_I32:
      r = (unsigned char)*(long*)self->data;
      break;
    case ELEMENT_U8:
      r = (unsigned char)*(unsigned char*)self->data;
      break;
    case ELEMENT_U16:
      r = (unsigned char)*(unsigned short*)self->data;
      break;
    case ELEMENT_U32:
      r = (unsigned char)*(unsigned long*)self->data;
      break;

    default:
      error(0, "unable to take u8");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

unsigned short element_take_u16(Element* self, int cleanup) {
  unsigned short r = 0;
  switch (self->kind) {
    case ELEMENT_I8:
      r = (unsigned short)*(char*)self->data;
      break;
    case ELEMENT_I16:
      r = (unsigned short)*(short*)self->data;
      break;
    case ELEMENT_I32:
      r = (unsigned short)*(long*)self->data;
      break;
    case ELEMENT_U8:
      r = (unsigned short)*(unsigned char*)self->data;
      break;
    case ELEMENT_U16:
      r = (unsigned short)*(unsigned short*)self->data;
      break;
    case ELEMENT_U32:
      r = (unsigned short)*(unsigned long*)self->data;
      break;

    default:
      error(0, "unable to take u16");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

unsigned long element_take_u32(Element* self, int cleanup) {
  unsigned long r = 0;
  switch (self->kind) {
    case ELEMENT_I8:
      r = (unsigned long)*(char*)self->data;
      break;
    case ELEMENT_I16:
      r = (unsigned long)*(short*)self->data;
      break;
    case ELEMENT_I32:
      r = (unsigned long)*(long*)self->data;
      break;
    case ELEMENT_U8:
      r = (unsigned long)*(unsigned char*)self->data;
      break;
    case ELEMENT_U16:
      r = (unsigned long)*(unsigned short*)self->data;
      break;
    case ELEMENT_U32:
      r = (unsigned long)*(unsigned long*)self->data;
      break;

    default:
      error(0, "unable to take u32");
      break;
  }

  if (cleanup) free(self->data);
  return r;
}

const char* element_data_to_cstring(Element* self) {
  char* tmp_str;
  switch (self->kind) {
    case ELEMENT_CSTRING:
      tmp_str = (char*)calloc(strlen((char*)self->data) + 1, sizeof(char));
      strcpy(tmp_str, (char*)self->data);
      return tmp_str;
      break;

    case ELEMENT_I8:
      tmp_str = (char*)calloc(5, sizeof(char));
      sprintf(tmp_str, "%hhi", *(char*)self->data);
      return tmp_str;
      break;
    case ELEMENT_I16:
      tmp_str = (char*)calloc(7, sizeof(short));
      sprintf(tmp_str, "%hi", *(short*)self->data);
      return tmp_str;
      break;
    case ELEMENT_I32:
      tmp_str = (char*)calloc(22, sizeof(long));
      sprintf(tmp_str, "%li", *(long*)self->data);
      return tmp_str;
      break;
    case ELEMENT_U8:
      tmp_str = (char*)calloc(5, sizeof(unsigned char));
      sprintf(tmp_str, "%hhu", *(unsigned char*)self->data);
      return tmp_str;
      break;
    case ELEMENT_U16:
      tmp_str = (char*)calloc(7, sizeof(unsigned short));
      sprintf(tmp_str, "%hu", *(unsigned short*)self->data);
      return tmp_str;
      break;
    case ELEMENT_U32:
      tmp_str = (char*)calloc(22, sizeof(unsigned long));
      sprintf(tmp_str, "%lu", *(unsigned long*)self->data);
      return tmp_str;
      break;

    default:
      error(0, "can't turn element value into string");
      break;
  }
  return "N/A";
}

const char* element_kind_to_cstring(Element* self) {
  switch (self->kind) {
    case ELEMENT_CSTRING:
      return "string";
      break;

    case ELEMENT_I8:
      return "i8";
      break;
    case ELEMENT_I16:
      return "i16";
      break;
    case ELEMENT_I32:
      return "i32";
      break;
    case ELEMENT_U8:
      return "u8";
      break;
    case ELEMENT_U16:
      return "u16";
      break;
    case ELEMENT_U32:
      return "u32";
      break;

    default:
      return "???";
      break;
  }
}

int element_is_signed_integer(Element* self) {
  switch (self->kind) {
    case ELEMENT_I8:
    case ELEMENT_I16:
    case ELEMENT_I32:
      return 1;
      break;

    default:
      return 0;
      break;
  }
}

int element_is_unsigned_integer(Element* self) {
  switch (self->kind) {
    case ELEMENT_U8:
    case ELEMENT_U16:
    case ELEMENT_U32:
      return 1;
      break;

    default:
      return 0;
      break;
  }
}

#endif