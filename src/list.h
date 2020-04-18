#ifndef LIST_H
#define LIST_H


#include <stdlib.h>
#include <string.h>
#include "element.h"

typedef struct{
    Element *elements;
    unsigned long top;
    unsigned long reserve;
}List;


List *newList(unsigned long initial_size){
    List *self = (List*)calloc(1, sizeof(*self));
    self->reserve = initial_size;
    self->top = 0;
    //self->elements = (Element*)calloc(self->reserve, self->size*sizeof(Element));
    self->elements = (Element*)calloc(self->reserve, sizeof(Element));
    //self->elements[0].kind = KIND_NOTHING;
    self->elements[0].kind = KIND_VOID;
    return self;
}

void list_resize(List *self, unsigned long size){
    self->elements = (Element*)realloc(self->elements, size*sizeof(Element));
}

int list_is_empty(List *self){
    return !self->top;
}

void list_push_bignum(List *self, Bignum* value){
    if (self->top+2 > self->reserve) {
        list_resize(self, self->top+2);
    }
    self->top++;
    element_from_bignum(&self->elements[self->top], value);
}

void list_pop_bignum(List *self, Bignum *result){
    if (self->top){
        element_as_bignum(&self->elements[self->top], result);
        self->top--;
    }else{
        free(result);
        result = NULL;
    }
}

void list_set_id(List *self, unsigned long index, char* id){
    free(self->elements[self->top].id);
    self->elements[self->top].id = (char *)malloc(strlen(id));
    strcpy(self->elements[self->top].id, id);
}

Element *list_get_pointer(List *self, unsigned long index){
    assert(index <= self->top);
    return &self->elements[index];
}

#endif