#ifndef DICTIONARY_H
#define DICTIONARY_H

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

int dictionary_has_key(Dictionary *self, char *key){
    unsigned long hash = hash_cstring(key);
    if (self->buckets[hash].top){

    }
    return 0;
}
void dictionary_forget(Dictionary *self, char *key){}
void dictionary_forget_all(Dictionary *self, char *key){}

/*
void dictionary_add(Dictionary *self, char *key, void *value){
    unsigned long bucket_index = hash_string(key) % self->bucket_count;
    //list_push(&self->buckets[bucket_index]);
    
}
*/


#endif