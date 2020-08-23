#ifndef RECONN_VM_H
#define RECONN_VM_H

#include "data/bucket.h"
#include "data/stack.h"
#include <assert.h>
#include <string.h>

typedef struct ReconnVM {
  // words to run
  ReconnStack run_stack;
  // words slated to be pushed to run stack
  ReconnStack slate_stack;
  // stack to contain values
  ReconnStack value_stack;
  // stack to store current namespace
  ReconnStack namespace_stack;

  // primary words
  ReconnBucket primary_words;
  // primary words
  ReconnBucket compile_words;
  // secondary words
  ReconnBucket secondary_words;
} ReconnVM;

ReconnVM reconn_makeVM() {
  ReconnVM self;
  self.run_stack = reconn_makeStack();
  self.slate_stack = reconn_makeStack();
  self.value_stack = reconn_makeStack();
  self.namespace_stack = reconn_makeStack();
  // push null
  reconn_stack_push_string(&self.namespace_stack, "\0", 1);
  return self;
}

void reconn_vm_enter_namespace(ReconnVM *self, char *nspace) {
  size_t length = strlen(nspace);
  size_t count = reconn_stack_count(&self->namespace_stack);

  if (count == 1) {
    // pop null
    reconn_stack_pop_void(&self->namespace_stack);
    // push string
    reconn_stack_push_string(&self->namespace_stack, nspace, length);
    // push null
    reconn_stack_push_string(&self->namespace_stack, "\0", 1);
  } else if (count >= 2) {
    // pop null
    reconn_stack_pop_void(&self->namespace_stack);
    // push seperator
    reconn_stack_push_string(&self->namespace_stack, ".", 1);
    // push namespace
    reconn_stack_push_string(&self->namespace_stack, nspace, length);
    // push null
    reconn_stack_push_string(&self->namespace_stack, "\0", 1);
  } else {
    assert(0);
  }
}

void reconn_vm_leave_namespace(ReconnVM *self) {
  size_t count = reconn_stack_count(&self->namespace_stack);
  if (count == 2) {
    // pop null
    reconn_stack_pop_void(&self->namespace_stack);
    // pop namespace
    reconn_stack_pop_void(&self->namespace_stack);
    // push null
    reconn_stack_push_string(&self->namespace_stack, "\0", 1);
  } else if (count > 2) {
    // pop null
    reconn_stack_pop_void(&self->namespace_stack);
    // pop namespace
    reconn_stack_pop_void(&self->namespace_stack);
    // pop seperator
    reconn_stack_pop_void(&self->namespace_stack);
    // push null
    reconn_stack_push_string(&self->namespace_stack, "\0", 1);
  } else {
    assert(0);
  }
}

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

// get fragment of namespace at given level/depth
char *reconn_vm_namespace_fragment(ReconnVM *self, size_t level) {
  const char *nspace = reconn_vm_get_namespace(self);
  size_t len = strlen(nspace);
  size_t depth = reconn_vm_namespace_depth(self);
  char sep = '.';
  char *fragment = calloc(1, len + 1);
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

void reconn_vm_do_token(ReconnVM *self, const char *token) {
  // reconn_bucket_get(self->primary_words, token);
}

void reconn_vm_tick(ReconnVM *self);
// void reconn_slate(ReconnVM *self);
// void reconn_flush(ReconnVM *self);

#endif