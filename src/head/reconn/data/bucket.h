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

void reconn_element_free(ReconnBucketItem *self, int free_self) {
  switch (self->kind) {
  case RECONN_VALUE_WORD_BUFFER:
    reconn_buffer_free((ReconnBuffer *)self->data, 1);
    break;

  case RECONN_VALUE_POINTER:
  case RECONN_VALUE_WORD_PRIMARY:
    break;

  default:
    // printf("FREE>%i<\n", self->kind);
    free(self->data);
    break;
  }
  free(self->id);

  if (free_self)
    free(self);
}

void reconn_bucket_free(ReconnBucket *self, int free_self) {
  for (int i = 0; i < stb_sb_count(self->cells); i++) {
    reconn_element_free(&(self->cells[i]), 0);
  }
  stb_sb_free(self->cells);
  if (free_self)
    free(self);
}

ReconnBucketItem reconn_makeBucketItem(void *data, ReconnValueKind kind,
                                       const char *id) {
  ReconnBucketItem self;
  self.data = data;
  self.kind = kind;

  size_t len = strlen(id);
  self.id = (char *)malloc(len + 1);
  // strncpy(self.id, id, len + 1);
  memcpy(self.id, id, len + 1);
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

size_t reconn_bucket_find(ReconnBucket *self, const char *id) {
  for (int i = 1; i < stb_sb_count(self->cells); i++) {
    if (self->cells[i].kind != RECONN_VALUE_EMPTY &&
        strcmp(self->cells[i].id, id) == 0) {
      return i;
    }
  }
  return 0;
}

size_t reconn_bucket_add(ReconnBucket *self, void *data, const char *id,
                         ReconnValueKind kind) {
  size_t index = reconn_bucket_first_free(self);
  if (index) {
    self->cells[index].data = data;
    self->cells[index].kind = kind;

    size_t len = strlen(id);
    self->cells[index].id = (char *)realloc(self->cells[index].id, len + 1);
    // strncpy(self->cells[index].id, id, len + 1);
    memcpy(self->cells[index].id, id, len + 1);

  } else {
    stb_sb_push(self->cells, reconn_makeBucketItem(data, kind, id));
    index = stb_sb_count(self->cells) - 1;
  }
  return index;
}

void *reconn_bucket_findv(ReconnBucket *self, const char *id) {
  size_t index = reconn_bucket_find(self, id);
  return self->cells[index].data;
}

void *reconn_bucket_get(ReconnBucket *self, size_t index) {
  return self->cells[index].data;
}

/*
// void reconn_bucket_remove_first(ReconnBucket *self);
void reconn_bucket_remove_all(ReconnBucket *self, const char *id) {
  for (int i = 1; i < stb_sb_count(self->cells); i++) {
    if (self->cells[i].kind != RECONN_VALUE_EMPTY &&
        strcmp(self->cells[i].id, id) == 0) {
      self->cells[i].kind = RECONN_VALUE_EMPTY;
    }
  }
}
*/

#endif