#ifndef ELEMENT_H
#define ELEMENT_H

//#include "vm.h"
#include <stdlib.h>
#include <string.h>

#include "bignum.h"
//#include "list.h"
//#include "dictionary.h"
//#include "vm.h"

typedef enum {
  ELEMENT_VOID,   // uninitialized
  ELEMENT_EMPTY,  // ready for contents
  ELEMENT_BIGNUM,
  ELEMENT_WORD_PRIMARY,
  ELEMENT_WORD_SECONDARY,
  ELEMENT_INT,
  ELEMENT_CSTRING,
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
  // recycleBignum(&self->data);
  self->kind = ELEMENT_EMPTY;
  // self->size = 0;
  return self;
}

Bignum* element_get_bignum(Element* self) { return (Bignum*)self->data; }

Element* element_set_bignum(Element* destination, Bignum* source) {
  destination->data = (void*)source;
  destination->kind = ELEMENT_BIGNUM;
  return destination;
}

int* element_get_int(Element* self) { return (int*)self->data; }

Element* element_set_int(Element* destination, int* source) {
  destination->data = (void*)source;
  destination->kind = ELEMENT_INT;
  return destination;
}

char* element_get_cstring(Element* self) { return (char*)self->data; }

Element* element_set_cstring(Element* destination, char* source) {
  destination->data = (void*)source;
  destination->kind = ELEMENT_CSTRING;
  return destination;
}

#endif