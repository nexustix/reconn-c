#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>

#include <stdlib.h>
#include "list.h"
#include "hash.h"
#include "bignum.h"

typedef struct{
    List *buckets;
    unsigned long bucket_count;
}Dictionary;


Dictionary *newDictionary(unsigned long bucket_count){
    Dictionary *self = (Dictionary *)calloc(1, sizeof(*self));
    self->bucket_count = bucket_count;
    self->buckets = (List*) calloc(self->bucket_count, sizeof(List));
    return self;
}

unsigned long dictionary_has_key(Dictionary *self, char *key){
    unsigned long hash = hash_cstring(key, self->bucket_count);
    if (self->buckets[hash].top){
        for (unsigned long i=0; i < self->buckets[hash].top; i++){
            unsigned long index = self->buckets[hash].top - i;
            Element *pointer = list_get_pointer(&self->buckets[hash], index);
            assert(pointer->id != NULL);
            if (strcmp(pointer->id, key)==0){
                return index;
            }
        }
    }
    return 0;
}

void dictionary_forget(Dictionary *self, char *key){
    unsigned long hash = hash_cstring(key, self->bucket_count);
    unsigned long index = dictionary_has_key(self, key);
    //if (index){
    //    self->buck
    //}
}

void dictionary_forget_all(Dictionary *self, char *key){}

/*
void dictionary_add(Dictionary *self, char *key, void *value){
    unsigned long bucket_index = hash_string(key) % self->bucket_count;
    //list_push(&self->buckets[bucket_index]);
    
}
*/

void dictionary_add_bignum(Dictionary *self, char *key, Bignum* value){
    unsigned long hash = hash_cstring(key, self->bucket_count);
    list_push_bignum(&self->buckets[hash], value);
    list_set_id(&self->buckets[hash], self->buckets[hash].top, key);
    //strcpy()
    //self->buckets[hash]->elements[self->buckets[hash].top].id = key;
    //strcpy(self->buckets[hash].elements[self->buckets[hash].top].id, key);
}


#endif