#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include "bignum.h"
// #include "element.h"

typedef struct{
    Bignum *elements;
    unsigned long top;
    unsigned long size;
}List;


List *newList(unsigned long initial_size){
    List *self = (List*)calloc(1, sizeof(*self));
    self->size = initial_size;
    self->top = 0;
    // self->elements = (Element*)calloc(self->size, sizeof(Element));
    // self->elements[0].kind = KIND_NOTHING;
    // free(self->elements[0].data);
    self->elements = (Bignum*)calloc(self->size, self->size*sizeof(Bignum));
    //free(&self->elements[0]);
    return self;
}

void list_resize(List *self, unsigned long size) {
    self->elements = (Bignum*)realloc(self->elements, size * sizeof(Bignum));
}

int list_is_empty(List *self){
    return !self->top;
}

void list_push(List *self, Bignum *value){
    if (self->top+2 > self->size) {
        list_resize(self, self->top+2);
    }
    self->top++;
    copyBignum(&self->elements[self->top], value);
}
void list_pop(List *self, Bignum *result){
    copyBignum(result, &self->elements[self->top]);
    self->top--;
}

void list_peek(List *self, Bignum *result){
    copyBignum(result, &self->elements[self->top]);
}


#endif