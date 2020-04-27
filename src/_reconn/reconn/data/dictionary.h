#ifndef RECONN_DATA_DICTIONARY_H
#define RECONN_DATA_DICTIONARY_H

#include <stdlib.h>

#include "element.h"
#include "hash.h"
#include "list.h"

typedef struct ReconnDictionary {
  ReconnList* buckets;
  unsigned long bucket_count;
} ReconnDictionary;

ReconnDictionary* rcn_newReconnDictionary(unsigned long bucket_count);

unsigned long rcn_dictionary_has_key(ReconnDictionary* self, const char* key);

int rcn_dictionary_forget(ReconnDictionary* self, const char* key);

void rcn_dictionary_forget_all(ReconnDictionary* self, const char* key);

void rcn_dictionary_add(ReconnDictionary* self, const char* key,
                        ReconnElement* value);

ReconnElement* rcn_dictionary_get(ReconnDictionary* self, const char* key);

#endif