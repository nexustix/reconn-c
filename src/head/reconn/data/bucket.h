#ifndef RECONN_DATA_BUCKET_H
#define RECONN_DATA_BUCKET_H

#include "stb/stretchy_buffer.h"
#include "value.h"
#include <string.h>

typedef struct ReconnBucketItem {
  void *data;
  ReconnValueKind kind;
  char *id;
} ReconnBucketItem;

typedef struct ReconnBucket {
  ReconnBucketItem *cells;
} ReconnBucket;

ReconnBucketItem reconn_makeBucketItem(void *data, ReconnValueKind kind,
                                       const char *id) {
  ReconnBucketItem self;
  self.data = data;
  self.kind = kind;

  size_t len = strlen(id);
  self.id = (char *)malloc(len + 1);
  strncpy(self.id, id, len + 1);
  return self;
}

ReconnBucket reconn_makeBucket() {
  ReconnBucket self;
  self.cells = NULL;
  stb_sb_push(self.cells, reconn_makeBucketItem(NULL, RECONN_VALUE_VOID, ""));
  return self;
}

size_t reconn_bucket_first_free(ReconnBucket *self) {
  for (int i = 1; i < stb_sb_count(self->cells); i++) {
    if (self->cells[i].kind == RECONN_VALUE_EMPTY) {
      return i;
    }
  }
  return 0;
}

size_t reconn_bucket_has_id(ReconnBucket *self, const char *id) {
  for (int i = 1; i < stb_sb_count(self->cells); i++) {
    if (self->cells[i].kind != RECONN_VALUE_EMPTY &&
        strcmp(self->cells[i].id, id) == 0) {
      return i;
    }
  }
  return 0;
}

size_t reconn_bucket_add(ReconnBucket *self, void *data, const char *id) {
  size_t index = reconn_bucket_first_free(self);
  if (index) {
    self->cells[index].data = data;
    self->cells[index].kind = RECONN_VALUE_POINTER;

    size_t len = strlen(id);
    self->cells[index].id = (char *)realloc(self->cells[index].id, len + 1);
    strncpy(self->cells[index].id, id, len + 1);

  } else {
    stb_sb_push(self->cells,
                reconn_makeBucketItem(data, RECONN_VALUE_POINTER, id));
    index = stb_sb_count(self->cells) - 1;
  }
  return index;
}

void *reconn_bucket_get(ReconnBucket *self, const char *id) {
  size_t index = reconn_bucket_has_id(self, id);
  return self->cells[index].data;
}

// void reconn_bucket_remove_first(ReconnBucket *self);
void reconn_bucket_remove_all(ReconnBucket *self, const char *id) {
  for (int i = 1; i < stb_sb_count(self->cells); i++) {
    if (self->cells[i].kind != RECONN_VALUE_EMPTY &&
        strcmp(self->cells[i].id, id) == 0) {
      self->cells[i].kind = RECONN_VALUE_EMPTY;
    }
  }
}

#endif