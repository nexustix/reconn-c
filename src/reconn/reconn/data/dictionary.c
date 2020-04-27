
#include "reconn/data/dictionary.h"

ReconnDictionary* rcn_newReconnDictionary(unsigned long bucket_count) {
  ReconnDictionary* self = (ReconnDictionary*)calloc(1, sizeof(*self));
  self->bucket_count = bucket_count;
  self->buckets = (ReconnList*)calloc(self->bucket_count, sizeof(ReconnList));
  return self;
}

unsigned long rcn_dictionary_has_key(ReconnDictionary* self, const char* key) {
  unsigned long hash = rcn_hash_cstring(key, self->bucket_count);
  if (self->buckets[hash].top) {
    for (unsigned long i = 0; i < self->buckets[hash].top; i++) {
      unsigned long index = self->buckets[hash].top - i;
      ReconnElement* pointer = rcn_list_get_at(&self->buckets[hash], index);
      assert(pointer->id != NULL);
      if ((pointer->kind != RECONN_ELEMENT_EMPTY) &&
          strcmp(pointer->id, key) == 0) {
        return index;
      }
    }
  }
  return 0;
}

int rcn_dictionary_forget(ReconnDictionary* self, const char* key) {
  unsigned long hash = rcn_hash_cstring(key, self->bucket_count);
  unsigned long index = rcn_dictionary_has_key(self, key);
  if (index) {
    rcn_list_remove_at(&self->buckets[hash], index);
  }
  return index;
}

void rcn_dictionary_forget_all(ReconnDictionary* self, const char* key) {
  while (rcn_dictionary_forget(self, key))
    ;
}

void rcn_dictionary_add(ReconnDictionary* self, const char* key,
                        ReconnElement* value) {
  unsigned long hash = rcn_hash_cstring(key, self->bucket_count);
  unsigned long index = rcn_list_insert(&self->buckets[hash], value);
  rcn_list_set_id(&self->buckets[hash], index, key);
}

ReconnElement* rcn_dictionary_get(ReconnDictionary* self, const char* key) {
  unsigned long hash = rcn_hash_cstring(key, self->bucket_count);
  unsigned long index = rcn_dictionary_has_key(self, key);
  if (index) {
    return rcn_list_get_at(&self->buckets[hash], index);
  }
  return NULL;
}
