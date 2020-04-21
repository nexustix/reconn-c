#ifndef VEEM_H
#define VEEM_H

//#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
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

void vm_state_push(VM* self, StateKind state){
  static Element* e;
  if (!e) e = newElement();

  StateKind *tmp = malloc(sizeof(StateKind));
  *tmp = state;
  list_push(self->state_stack, element_set_int(e, (int*)tmp));
}

StateKind vm_state_pop(VM* self){
  static Element* e;
  if (!e) e = newElement();

  //assert(!list_is_empty(self->state_stack));
  error(!list_is_empty(self->state_stack), "tried popping from empty state stack");
  StateKind *state = (StateKind*)element_get_int(list_pop(self->state_stack, e));
  return *state;
  free(state);
  //return (StateKind)*element_get_int(list_pop(self->state_stack, e));
}

void vm_add_primary(VM* self, char* token, void (*callback)(VM*)) {
  static Element* e;
  if (!e) e = newElement();

  e->kind = ELEMENT_WORD_PRIMARY;
  dictionary_add(self->dictionaries[STATE_NORMAL], token,
                 element_set_pword(e, callback));
}

void vm_add_secondary(VM* self, char* token, List* source) {
  static Element* e;
  if (!e) e = newElement();

  e->kind = ELEMENT_WORD_SECONDARY;
  dictionary_add(self->dictionaries[STATE_NORMAL], token,
                 element_set_sword(e, source));
}

void vm_add_compile(VM* self, char* token, void (*callback)(VM*)) {
  static Element* e;
  if (!e) e = newElement();

  e->kind = ELEMENT_WORD_PRIMARY;
  dictionary_add(self->dictionaries[STATE_COMPILE], token,
                 element_set_pword(e, callback));
}

void vm_wordbuffer_push(VM* self, char *token){
  static Element* e;
  if (!e) e = newElement();

  list_push(self->word_buffer, element_set_cstring(e, token));
}
char *vm_wordbuffer_pop(VM *self){
  static Element* e;
  if (!e) e = newElement();
  
  return element_get_cstring(list_pop(self->word_buffer, e));
}

void vm_do(VM* self, char* token) {
  static Element* e;
  if (!e) e = newElement();

  if (strcmp("(", token) ==0) self->comment++;
  else if (strcmp(")", token) ==0){
    self->comment--;
    //assert(self->comment >= 0);
    error(self->comment >= 0, "unbalanced comments");
  }
  if (self->comment) return;

  int state = vm_state(self);
  switch (state) {
    case STATE_NORMAL:
      if (dictionary_has_key(self->dictionaries[STATE_NORMAL], token)) {
        e = dictionary_get(self->dictionaries[STATE_NORMAL], token);
        if (e->kind == ELEMENT_WORD_PRIMARY) {
          element_get_pword(e)(self);
        } else if (e->kind == ELEMENT_WORD_SECONDARY) {
          List* words = element_get_sword(e);
          for (unsigned long i = 0; i < words->top; i++) {
            e = list_get_at(words, words->top - i);
            //assert(e->kind == ELEMENT_CSTRING);
            error(e->kind == ELEMENT_CSTRING, "non-cstring in secondary word");
            list_push(self->run_stack, e);
          }
        }
      } else {
        printf("no idea what >%s< means\n", token);
        //TODO turn words into values
      }
      break;

    case STATE_COMPILE:
      if (dictionary_has_key(self->dictionaries[STATE_COMPILE], token)) {
        e = dictionary_get(self->dictionaries[STATE_COMPILE], token);
        //assert(e->kind == ELEMENT_WORD_PRIMARY);
        error(e->kind == ELEMENT_WORD_PRIMARY, "tried to call non-primary from dictionary");
        element_get_pword(e)(self);
      }else{
        list_push(self->word_buffer, element_set_cstring(e, token));
      }
      break;

    case STATE_HARD:
      if (strcmp(TOKEN_END, token)){
        vm_state_pop(self);
      }else{
        list_push(self->word_buffer, element_set_cstring(e, token));
      }
      break;

    default:
      break;
  }
}
void vm_run(VM* self) {
  static Element* e;
  if (!e) e = newElement();
  while(! list_is_empty(self->run_stack)){
    list_pop(self->run_stack, e);
    if (e->kind == ELEMENT_CSTRING){
      vm_do(self, element_get_cstring(e));
    }
  }
}

#endif