#ifndef VEEM_H
#define VEEM_H

//#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "ducktype.h"
#include "element.h"
#include "list.h"
#include "util.h"

#define TOKEN_DEF "def"
#define TOKEN_END "end"

typedef enum {
  STATE_NORMAL,
  STATE_COMPILE,

  STATE_HARD,
  STATE_COUNT,
} StateKind;

typedef enum {
  WORD_PRIMARY,
  WORD_SECONDARY,
  WORD_COMPILE,
} WordKind;

typedef struct VM {
  List* run_stack;
  List* value_stack;
  List* state_stack;
  List* namespace_stack;

  Dictionary** dictionaries;

  List* word_buffer;

  int comment;
  int running;

  unsigned int base;
} VM;

void (*element_get_pword(Element* self))(VM*) {
  return (void (*)(VM*))self->data;
}

Element* element_set_pword(Element* destination, void (*source)(VM*)) {
  destination->data = (void*)source;
  destination->kind = ELEMENT_WORD_PRIMARY;
  return destination;
}

List* element_get_sword(Element* self) { return (List*)self->data; }

Element* element_set_sword(Element* destination, List* source) {
  destination->data = (void*)source;
  destination->kind = ELEMENT_WORD_SECONDARY;
  return destination;
}

VM* newVM() {
  // VM *self = (VM*)calloc(1, sizeof(*self));
  VM* self = (VM*)malloc(sizeof(*self));
  self->run_stack = newList(8);
  self->value_stack = newList(8);
  self->state_stack = newList(8);
  self->namespace_stack = newList(8);
  self->dictionaries =
      (Dictionary**)calloc(STATE_COUNT - 1, sizeof(Dictionary*));
  for (int i = 0; i < STATE_COUNT; i++) {
    self->dictionaries[i] = newDictionary(0xfff);
  }
  self->word_buffer = newList(0xff);
  self->comment = 0;
  self->running = 1;
  return self;
}

StateKind vm_state(VM* self) {
  // static Element *e = newElement();
  if (list_is_empty(self->state_stack)) {
    return STATE_NORMAL;
  }
  return (StateKind)*element_get_int(
      list_get_at(self->state_stack, self->state_stack->top));

  // return STATE_NORMAL;
}

void vm_push_state(VM* self, StateKind state) {
  static Element* e;
  if (!e) e = newElement();

  StateKind* tmp = malloc(sizeof(StateKind));
  *tmp = state;
  list_push(self->state_stack, element_set_int(e, (int*)tmp));
}

StateKind vm_pop_state(VM* self) {
  static Element* e;
  if (!e) e = newElement();

  // assert(!list_is_empty(self->state_stack));
  error(!list_is_empty(self->state_stack),
        "tried popping from empty state stack");
  StateKind* state =
      (StateKind*)element_get_int(list_pop(self->state_stack, e));
  return *state;
  free(state);
  // return (StateKind)*element_get_int(list_pop(self->state_stack, e));
}

void vm_add_primary(VM* self, const char* token, void (*callback)(VM*)) {
  static Element* e;
  if (!e) e = newElement();

  e->kind = ELEMENT_WORD_PRIMARY;
  dictionary_add(self->dictionaries[STATE_NORMAL], token,
                 element_set_pword(e, callback));
}

void vm_add_secondary(VM* self, const char* token, List* source) {
  static Element* e;
  if (!e) e = newElement();

  e->kind = ELEMENT_WORD_SECONDARY;
  dictionary_add(self->dictionaries[STATE_NORMAL], token,
                 element_set_sword(e, source));
}

void vm_add_compile(VM* self, const char* token, void (*callback)(VM*)) {
  static Element* e;
  if (!e) e = newElement();

  e->kind = ELEMENT_WORD_PRIMARY;
  dictionary_add(self->dictionaries[STATE_COMPILE], token,
                 element_set_pword(e, callback));
}

void vm_push_wordbuffer(VM* self, const char* token) {
  static Element* e;
  if (!e) e = newElement();

  list_push(self->word_buffer, element_set_cstring(e, token));
}
const char* vm_pop_wordbuffer(VM* self) {
  static Element* e;
  if (!e) e = newElement();

  return element_get_cstring(list_pop(self->word_buffer, e));
}

void vm_push_value(VM* self, Element* value) {
  list_push(self->value_stack, value);
}
Element* vm_pop_value(VM* self, Element* value) {
  return list_pop(self->value_stack, value);
}

char* vm_namespace(VM* self) {
  // // FIXME will fail with huge namespaces
  // char* namespace = calloc(2048, 1);
  char* namespace = calloc(1024, 1);
  // char* namespace = "";
  if (self->namespace_stack->top > 0) {
    for (unsigned int i = 1; i <= self->namespace_stack->top; i++) {
      if (!i) strcat(namespace, ".");
      strcat(namespace,
             element_get_cstring(list_get_at(self->namespace_stack, i)));
      if (i < self->namespace_stack->top) strcat(namespace, ".");
    }
  }
  return namespace;
}

void vm_push_namespace(VM* self, const char* name) {
  static Element* e;
  if (!e) e = newElement();

  list_push(self->namespace_stack, element_set_cstring(e, name));
}

const char* vm_pop_namespace(VM* self) {
  static Element* e;
  if (!e) e = newElement();
  error(self->namespace_stack->top,
        "Can't leave namespace while not inside "
        "namespace");
  return element_get_cstring(list_pop(self->namespace_stack, e));
}

Element* vm_find_word(VM* self, const char* token) {
  char* namespace = vm_namespace(self);
  size_t namespace_length = strlen(namespace);
  size_t token_length = strlen(token);
  char* wordname = calloc(namespace_length + token_length + 1, 1);
  Element* result;

  // HACK
  while (1) {
    wordname[0] = 0;
    if (namespace[0]) {
      strcat(wordname, namespace);
      strcat(wordname, ".");
      strcat(wordname, token);
    } else {
      strcat(wordname, token);
    }
    result = dictionary_get(self->dictionaries[vm_state(self)], wordname);
    if (result) return result;
    if (!namespace[0]) break;
    seplob(namespace, '.');
  }
  return NULL;
}

int vm_do(VM* self, const char* token) {
  // static Element* e;
  // if (!e) e = newElement();

  // FIXME - comb for memory leaks
  Element* e = newElement();

  // fprintf(stderr, " - do >%s< inside >%d<\n", token, (int)vm_state(self));

  if (strcmp("(", token) == 0)
    self->comment++;
  else if (strcmp(")", token) == 0) {
    self->comment--;
    // assert(self->comment >= 0);
    error(self->comment >= 0, "unbalanced comments");
  }
  if (self->comment) return 0;

  int state = vm_state(self);
  switch (state) {
    case STATE_NORMAL:
      // fprintf(stderr, " - inside NORMAL\n");
      if (dictionary_has_key(self->dictionaries[STATE_NORMAL], token)) {
        e = dictionary_get(self->dictionaries[STATE_NORMAL], token);
        if (e->kind == ELEMENT_WORD_PRIMARY) {
          // fprintf(stderr, " - found prime\n");
          element_get_pword(e)(self);
        } else if (e->kind == ELEMENT_WORD_SECONDARY) {
          // fprintf(stderr, " - found secondary\n");
          List* words = element_get_sword(e);
          for (unsigned long i = 0; i < words->top; i++) {
            e = list_get_at(words, words->top - i);
            // assert(e->kind == ELEMENT_CSTRING);
            error(e->kind == ELEMENT_CSTRING, "non-cstring in secondary word");
            list_push(self->run_stack, e);
          }
        } else {
          error(0, "non-word in dictionary");
        }
      } else {
        Element* element = ducktype_as_whatever(token, 1);
        if (element) {
          switch (element->kind) {
            case ELEMENT_CSTRING:
              element_set_bignum(
                  element, bignum_copy_cstring(element_get_cstring(element)));
              vm_push_value(self, element);
              return 0;
              break;

            case ELEMENT_BIGNUM:
              vm_push_value(self, element);
              return 0;
              break;

            default:
              error(0, "value resolved to invalid type");
              break;
          }
        } else {
          fprintf(stderr, " ! no idea what >%s< means\n", token);
        }
        return 1;
      }
      break;

    case STATE_COMPILE:
      // fprintf(stderr, " - inside COMPILE\n");
      if (dictionary_has_key(self->dictionaries[STATE_COMPILE], token)) {
        e = dictionary_get(self->dictionaries[STATE_COMPILE], token);
        // assert(e->kind == ELEMENT_WORD_PRIMARY);
        error(e->kind == ELEMENT_WORD_PRIMARY,
              "tried to call non-primary from dictionary");
        element_get_pword(e)(self);
      } else {
        list_push(self->word_buffer, element_set_cstring(e, token));
      }
      break;

    case STATE_HARD:
      // fprintf(stderr, " - inside HARD COMPILE\n");
      if (strcmp(TOKEN_END, token) == 0) {
        vm_push_wordbuffer(self, TOKEN_END);
        vm_pop_state(self);
      } else {
        list_push(self->word_buffer, element_set_cstring(e, token));
      }
      break;

    default:
      break;
  }
  return 0;
}

int vm_run(VM* self) {
  static Element* e;
  if (!e) e = newElement();
  while (!list_is_empty(self->run_stack)) {
    list_pop(self->run_stack, e);
    if (e->kind == ELEMENT_CSTRING) {
      if (vm_do(self, element_get_cstring(e))) return 1;
      ;
    }
  }
  return 0;
}

int vm_execute(VM* self, const char* word) {
  int r;
  r = vm_do(self, word);
  // FIXME refine, doesn't care abour half compiled words
  if (r) {
    self->run_stack->top = 0;
    return r;
  }
  r = vm_run(self);
  if (r) {
    self->run_stack->top = 0;
    return r;
  }
  return 0;
}

int vm_execute_all(VM* self, List* words, int ok) {
  for (unsigned long i = 1; i <= words->top; i++) {
    if (vm_execute(self, element_get_cstring(list_get_at(words, i)))) {
      if (ok) fprintf(stderr, " ! ERR\n");
      return 1;
    }
  }
  if (ok) fprintf(stderr, " - OK\n");
  return 0;
}

#endif