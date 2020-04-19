#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdlib.h>
#include <string.h>

#include "bignum.h"

typedef enum {
  KIND_VOID,   // uninitialized
  KIND_EMPTY,  // ready for contents
  KIND_BIGNUM,
  KIND_WORD_PRIMARY,
  KIND_WORD_SECONDARY,
  KIND_INT,
  KIND_CSTRING,
} ElementKind;

typedef struct {
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
  self->kind = KIND_EMPTY;
  // self->size = 0;
  return self;
}

/*
void recycleElement(Element *self){
    self->kind = KIND_EMPTY;
    //self->size = 0;
    free(self->data);
    //recycleBignum(&self->data);
}
*/

/*
void copyElement(Element *destination, Element *source){
    // destination->data = source->data;
    // destination->kind = source->kind;
    //memcpy(destination, source, sizeof(Element));
    //copyBignum(&destination->data, &source->data);

    //copyBignum(&destination->data, &source->data);
    //destination->kind = source->kind;
}
*/

/*
void element_as_bignum(Element *self, Bignum *destination){
    //copyBignum(destination, (Bignum*)self->data);

    dupBignum(destination, (Bignum*)self->data);

}

void element_from_bignum(Element *self, Bignum *source){
    //copyBignum((Bignum*)self->data, source);
    //recycleElement(self);
    free(self->data);
    self->data = malloc(sizeof(Bignum));
    dupBignum((Bignum*)self->data, source);
    self->kind = KIND_BIGNUM;
}
*/

Bignum* element_get_bignum(Element* self) { return (Bignum*)self->data; }

Element* element_set_bignum(Element* destination, Bignum* source) {
  destination->data = (void*)source;
  destination->kind = KIND_BIGNUM;
  return destination;
}

int* element_get_int(Element* self) { return (int*)self->data; }

Element* element_set_int(Element* destination, int* source) {
  destination->data = (void*)source;
  destination->kind = KIND_INT;
  return destination;
}

char* element_get_cstring(Element* self) { return (char*)self->data; }

Element* element_set_cstring(Element* destination, char* source) {
  destination->data = (void*)source;
  destination->kind = KIND_INT;
  return destination;
}

#endif