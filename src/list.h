#ifndef LIST_H
#define LIST_H


#include <stdlib.h>
#include <string.h>
#include "element.h"

typedef struct{
    Element *elements;
    unsigned long top;
    unsigned long size;
}List;


List *newList(unsigned long initial_size){
    List *self = (List*)calloc(1, sizeof(*self));
    self->size = initial_size;
    self->top = 0;
    self->elements = (Element*)calloc(self->size, self->size*sizeof(Element));
    self->elements[0].kind = KIND_NOTHING;
    return self;
}

void list_resize(List *self, unsigned long size){
    self->elements = (Element*)realloc(self->elements, size*sizeof(Element));
}

int list_is_empty(List *self){
    return !self->top;
}

void list_push_bignum(List *self, Bignum* value){
    if (self->top+2 > self->size) {
        list_resize(self, self->top+2);
    }
    self->top++;
    element_from_bignum(&self->elements[self->top], value);
}

void list_pop_bignum(List *self, Bignum *result){
    element_to_bignum(&self->elements[self->top], result);
    self->top--;
}

#endif