#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>

//#include "bignum.h"
#include "hash.h"
#include "list.h"

typedef struct Dictionary {
  List* buckets;
  unsigned long bucket_count;
} Dictionary;

Dictionary* newDictionary(unsigned long bucket_count) {
  Dictionary* self = (Dictionary*)calloc(1, sizeof(*self));
  self->bucket_count = bucket_count;
  self->buckets = (List*)calloc(self->bucket_count, sizeof(List));
  return self;
}

unsigned long dictionary_has_key(Dictionary* self, const char* key) {
  unsigned long hash = hash_cstring(key, self->bucket_count);
  if (self->buckets[hash].top) {
    for (unsigned long i = 0; i < self->buckets[hash].top; i++) {
      unsigned long index = self->buckets[hash].top - i;
      Element* pointer = list_get_at(&self->buckets[hash], index);
      assert(pointer->id != NULL);
      if ((pointer->kind != ELEMENT_EMPTY) && strcmp(pointer->id, key) == 0) {
        return index;
      }
    }
  }
  return 0;
}

int dictionary_forget(Dictionary* self, const char* key) {
  unsigned long hash = hash_cstring(key, self->bucket_count);
  unsigned long index = dictionary_has_key(self, key);
  if (index) {
    list_remove_at(&self->buckets[hash], index);
  }
  return index;
}

void dictionary_forget_all(Dictionary* self, const char* key) {
  while (dictionary_forget(self, key))
    ;
}

void dictionary_add(Dictionary* self, const char* key, Element* value) {
  unsigned long hash = hash_cstring(key, self->bucket_count);
  unsigned long index = list_insert(&self->buckets[hash], value);
  list_set_id(&self->buckets[hash], index, key);
}

Element* dictionary_get(Dictionary* self, const char* key) {
  unsigned long hash = hash_cstring(key, self->bucket_count);
  unsigned long index = dictionary_has_key(self, key);
  if (index) {
    return list_get_at(&self->buckets[hash], index);
  }
  return NULL;
}

#endif