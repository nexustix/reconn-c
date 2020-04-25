#ifndef ELEMENT_H
#define ELEMENT_H

//#include "vm.h"
#include <stdlib.h>
#include <string.h>

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

void element_take_i8(Element* self) {}
void element_take_i16(Element* self) {}
void element_take_i32(Element* self) {}

void element_take_u8(Element* self) {}
void element_take_u16(Element* self) {}
void element_take_u32(Element* self) {}

#endif