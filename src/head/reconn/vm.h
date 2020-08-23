#ifndef RECONN_VM_H
#define RECONN_VM_H

#include "data/bucket.h"
//#include "data/stack.h"
#include "data/buffer.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct ReconnVM {
  // words to run
  ReconnBuffer run_stack;
  // words slated to be pushed to run stack
  ReconnBuffer slate_stack;
  // stack to contain values
  ReconnBuffer value_stack;
  // stack to store current namespace
  ReconnBuffer namespace_stack;
  // primary words
  ReconnBucket primary_words;
  // secondary words
  ReconnBucket secondary_words;

  // word buffer
  // -> array of words ?
  ReconnBuffer compile_buffer;

  // namespace depth
  size_t ndepth;

} ReconnVM;

ReconnVM reconn_makeVM() {
  ReconnVM self;
  self.run_stack = reconn_makeBuffer();
  self.slate_stack = reconn_makeBuffer();
  self.value_stack = reconn_makeBuffer();
  self.namespace_stack = reconn_makeBuffer();
  self.compile_buffer = reconn_makeBuffer();

  self.primary_words = reconn_makeBucket();
  self.secondary_words = reconn_makeBucket();

  self.ndepth = 0;
  // push null
  reconn_buffer_push_string(&self.namespace_stack, "\0", 1);
  return self;
}

void reconn_vm_free(ReconnVM *self) {

  reconn_buffer_free(&self->run_stack, 0);
  reconn_buffer_free(&self->slate_stack, 0);
  reconn_buffer_free(&self->value_stack, 0);
  reconn_buffer_free(&self->namespace_stack, 0);
  reconn_buffer_free(&self->compile_buffer, 0);
  reconn_bucket_free(&self->primary_words, 0);
  reconn_bucket_free(&self->secondary_words, 0);
}

/*
=========
NAMESPACE
=========
*/

// get complete namespace as string
const char *reconn_vm_get_namespace(ReconnVM *self) {
  return (const char *)self->namespace_stack.data;
}

// get current depth of namespace
size_t reconn_vm_namespace_depth(ReconnVM *self) {
  size_t depth = 0;
  char sep = '.';
  const char *nspace = reconn_vm_get_namespace(self);
  if (!nspace[0]) {
    return depth;
  } else {
    depth += 1;
    size_t len = strlen(nspace);
    for (size_t i = 0; i < len; i++) {
      if (nspace[i] == sep) {
        depth += 1;
      }
    }
  }
  return depth;
}

void reconn_vm_enter_namespace(ReconnVM *self, char *nspace) {
  size_t length = strlen(nspace);
  size_t count = reconn_buffer_count(&self->namespace_stack);

  if (count == 1) {
    // pop null
    reconn_buffer_pop_void(&self->namespace_stack);
    // push string
    reconn_buffer_push_string(&self->namespace_stack, nspace, length);
    // push null
    reconn_buffer_push_string(&self->namespace_stack, "\0", 1);
  } else if (count >= 2) {
    // pop null
    reconn_buffer_pop_void(&self->namespace_stack);
    // push seperator
    reconn_buffer_push_string(&self->namespace_stack, ".", 1);
    // push namespace
    reconn_buffer_push_string(&self->namespace_stack, nspace, length);
    // push null
    reconn_buffer_push_string(&self->namespace_stack, "\0", 1);
  } else {
    assert(0);
  }

  self->ndepth = reconn_vm_namespace_depth(self);
}

void reconn_vm_leave_namespace(ReconnVM *self) {
  size_t count = reconn_buffer_count(&self->namespace_stack);
  if (count == 2) {
    // pop null
    reconn_buffer_pop_void(&self->namespace_stack);
    // pop namespace
    reconn_buffer_pop_void(&self->namespace_stack);
    // push null
    reconn_buffer_push_string(&self->namespace_stack, "\0", 1);
  } else if (count > 2) {
    // pop null
    reconn_buffer_pop_void(&self->namespace_stack);
    // pop namespace
    reconn_buffer_pop_void(&self->namespace_stack);
    // pop seperator
    reconn_buffer_pop_void(&self->namespace_stack);
    // push null
    reconn_buffer_push_string(&self->namespace_stack, "\0", 1);
  } else {
    assert(0);
  }

  self->ndepth = reconn_vm_namespace_depth(self);
}

// get fragment of namespace at given level/depth
char *reconn_vm_namespace_fragment(ReconnVM *self, size_t level) {
  const char *nspace = reconn_vm_get_namespace(self);
  size_t len = strlen(nspace);
  size_t depth = self->ndepth;
  char sep = '.';
  char *fragment = (char *)calloc(1, len + 1);
  assert(level <= depth);

  if (level == 0) {
  } else if (depth == 1 || depth == level) {
    strncpy(fragment, nspace, len);
  } else {
    size_t sep_count = 0;
    for (size_t i = 0; i < len; i++) {
      if (nspace[i] == sep) {
        sep_count += 1;
      }
      if (sep_count >= level) {
        strncpy(fragment, nspace, i);
        break;
      }
    }
  }
  return fragment;
}

// prepend namespace of certain level to token
char *reconn_vm_namespace_token(ReconnVM *self, const char *token,
                                size_t level) {
  char *nspace = reconn_vm_namespace_fragment(self, level);
  char *dest = (char *)calloc(1, strlen(nspace) + strlen(token) + 2);
  if (nspace[0]) {
    strcat(dest, nspace);
    strcat(dest, ".");
    strcat(dest, token);
  } else {
    strcat(dest, token);
  }
  free(nspace);
  return dest;
}

/*
=====
WORDS
=====
*/

/*
void rcn_vm_add_primary(ReconnVM *self, const char *token,
                        int (*callback)(ReconnVM *)) {
  static ReconnElement *e;
  if (!e)
    e = rcn_newReconnElement();

  e->kind = RECONN_ELEMENT_WORD_PRIMARY;
  rcn_dictionary_add(self->dictionaries[RECONN_STATE_NORMAL],
                     rcn_vm_spacename(self, token),
                     rcn_element_set_pword(e, callback));
}

void rcn_vm_add_secondary(ReconnVM *self, const char *token,
                          ReconnList *source) {
  static ReconnElement *e;
  if (!e)
    e = rcn_newReconnElement();

  e->kind = RECONN_ELEMENT_WORD_SECONDARY;
  rcn_dictionary_add(self->dictionaries[RECONN_STATE_NORMAL],
                     rcn_vm_spacename(self, token),
                     rcn_element_set_sword(e, source));
}
*/

void reconn_vm_add_primary(ReconnVM *self, const char *token,
                           int (*callback)(ReconnVM *)) {
  char *ntoken = reconn_vm_namespace_token(self, token, self->ndepth);
  reconn_bucket_add(&self->primary_words, callback, ntoken);
  free(ntoken);
}

/*
======
TOKENS
======
*/

void reconn_vm_do_token(ReconnVM *self, const char *token) {

  for (size_t d = self->ndepth; d >= 0; d--) {
    char *ntoken = reconn_vm_namespace_token(self, token, d);
    int (*fun)(ReconnVM *) = reconn_bucket_findv(&self->primary_words, ntoken);
    if (fun) {
      printf(">%s<FOUND!!!\n", ntoken);
      fun(self);
      return; // success
    } else {
      printf(">%s<nope\n", ntoken);
    }
    free(ntoken);
  }
  // reconn_bucket_get(self->primary_words, token);
}

void reconn_vm_tick(ReconnVM *self);
// void reconn_slate(ReconnVM *self);
// void reconn_flush(ReconnVM *self);

#endif