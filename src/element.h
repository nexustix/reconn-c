#ifndef ELEMENT_H
#define ELEMENT_H

#include <string.h>
#include <stdlib.h>
#include "bignum.h"


typedef enum {
    KIND_VOID,  // uninitialized
    KIND_EMPTY, // ready for contents
    KIND_NOTHING, // contains "nothing"
    KIND_BIGNUM
}ElementKind;

typedef struct{
    //void *data;
    Bignum data;
    ElementKind kind;
    //unsigned int size;
}Element;

Element *newElement(){
    Element *self = (Element *)calloc(1, sizeof(*self));
    //self->data = NULL;
    recycleBignum(&self->data);
    self->kind = KIND_EMPTY;
    //self->size = 0;
    return self;
}

void recycleElement(Element *self){
    self->kind = KIND_EMPTY;
    //self->size = 0;
    //free(self->data);
    recycleBignum(&self->data);
}


void copyElement(Element *destination, Element *source){
    // destination->data = source->data;
    // destination->kind = source->kind;
    //memcpy(destination, source, sizeof(Element));
    copyBignum(&destination->data, &source->data);
    destination->kind = source->kind;
}


void element_to_bignum(Element *self, Bignum *destination){
    //copyBignum(destination, (Bignum*)self->data);
    copyBignum(destination, &self->data);
}

void element_from_bignum(Element *self, Bignum *source){
    //free(self->data);
    //self->size = sizeof(Bignum);
    //self->data = malloc(self->size);
    //copyBignum((Bignum*)self->data, source);
    //self->kind = KIND_BIGNUM;
    copyBignum(&self->data, source);
}



#endif