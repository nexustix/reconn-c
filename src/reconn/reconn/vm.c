#include "reconn/vm.h"

int (*rcn_element_get_pword(ReconnElement* self))(ReconnVM*) {
  return (int (*)(ReconnVM*))self->data;
}

ReconnElement* rcn_element_set_pword(ReconnElement* destination,
                                     int (*source)(ReconnVM*)) {
  destination->data = (void*)source;
  destination->kind = RECONN_ELEMENT_WORD_PRIMARY;
  return destination;
}

ReconnList* rcn_element_get_sword(ReconnElement* self) {
  return (ReconnList*)self->data;
}

ReconnElement* rcn_element_set_sword(ReconnElement* destination,
                                     ReconnList* source) {
  destination->data = (void*)source;
  destination->kind = RECONN_ELEMENT_WORD_SECONDARY;
  return destination;
}

ReconnVM* rcn_newReconnVM() {
  // ReconnVM *self = (ReconnVM*)calloc(1, sizeof(*self));
  ReconnVM* self = (ReconnVM*)malloc(sizeof(*self));
  self->run_stack = rcn_newReconnList(8);
  self->value_stack = rcn_newReconnList(8);
  self->state_stack = rcn_newReconnList(8);
  self->namespace_stack = rcn_newReconnList(8);
  self->dictionaries = (ReconnDictionary**)calloc(RECONN_STATE_COUNT - 1,
                                                  sizeof(ReconnDictionary*));
  for (int i = 0; i < RECONN_STATE_COUNT; i++) {
    self->dictionaries[i] = rcn_newReconnDictionary(0xfff);
  }
  self->word_buffer = rcn_newReconnList(0xff);
  self->comment = 0;
  self->running = 1;
  return self;
}

ReconnStateKind rcn_vm_state(ReconnVM* self) {
  // static ReconnElement *e = newReconnElement();
  if (rcn_list_is_empty(self->state_stack)) {
    return RECONN_STATE_NORMAL;
  }
  return (ReconnStateKind)*rcn_element_get_enum(
      rcn_list_get_at(self->state_stack, self->state_stack->top));

  // return RECONN_STATE_NORMAL;
}

void rcn_vm_push_state(ReconnVM* self, ReconnStateKind state) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  ReconnStateKind* tmp = malloc(sizeof(ReconnStateKind));
  *tmp = state;
  rcn_list_push(self->state_stack, rcn_element_set_enum(e, (int*)tmp));
}

ReconnStateKind rcn_vm_pop_state(ReconnVM* self) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  // assert(!list_is_empty(self->state_stack));
  rcn_error(!rcn_list_is_empty(self->state_stack),
            "tried popping from empty state stack");
  ReconnStateKind* state = (ReconnStateKind*)rcn_element_get_enum(
      rcn_list_pop(self->state_stack, e));
  return *state;
  free(state);
  // return (ReconnStateKind)*element_get_int(list_pop(self->state_stack, e));
}

char* rcn_vm_namespace(ReconnVM* self) {
  // // FIXME will fail with huge namespaces
  // char* namespace = calloc(2048, 1);
  char* namespace = calloc(1024, 1);
  // char* namespace = "";
  if (self->namespace_stack->top > 0) {
    for (unsigned int i = 1; i <= self->namespace_stack->top; i++) {
      if (!i) strcat(namespace, ".");
      strcat(namespace, rcn_element_get_cstring(
                            rcn_list_get_at(self->namespace_stack, i)));
      if (i < self->namespace_stack->top) strcat(namespace, ".");
    }
  }
  return namespace;
}

void rcn_vm_push_namespace(ReconnVM* self, const char* name) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  rcn_list_push(self->namespace_stack, rcn_element_set_cstring(e, name));
}

const char* rcn_vm_pop_namespace(ReconnVM* self) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();
  rcn_error(self->namespace_stack->top,
            "Can't leave namespace while not inside "
            "namespace");
  return rcn_element_get_cstring(rcn_list_pop(self->namespace_stack, e));
}

const char* rcn_vm_spacename(ReconnVM* self, const char* token) {
  char* namespace = rcn_vm_namespace(self);
  size_t namespace_length = strlen(namespace);
  size_t token_length = strlen(token);
  char* spacename = calloc(token_length + namespace_length + 1, 1);

  if (namespace[0]) {
    strcpy(spacename, namespace);
    strcat(spacename, ".");
    strcat(spacename, token);
  } else {
    strcat(spacename, token);
  }

  free(namespace);
  return spacename;
}

void rcn_vm_add_primary(ReconnVM* self, const char* token,
                        int (*callback)(ReconnVM*)) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  e->kind = RECONN_ELEMENT_WORD_PRIMARY;
  rcn_dictionary_add(self->dictionaries[RECONN_STATE_NORMAL],
                     rcn_vm_spacename(self, token),
                     rcn_element_set_pword(e, callback));
}

void rcn_vm_add_secondary(ReconnVM* self, const char* token,
                          ReconnList* source) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  e->kind = RECONN_ELEMENT_WORD_SECONDARY;
  rcn_dictionary_add(self->dictionaries[RECONN_STATE_NORMAL],
                     rcn_vm_spacename(self, token),
                     rcn_element_set_sword(e, source));
}

void rcn_vm_add_compile(ReconnVM* self, const char* token,
                        int (*callback)(ReconnVM*)) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  e->kind = RECONN_ELEMENT_WORD_PRIMARY;
  rcn_dictionary_add(self->dictionaries[RECONN_STATE_COMPILE],
                     rcn_vm_spacename(self, token),
                     rcn_element_set_pword(e, callback));
}

void rcn_vm_push_wordbuffer(ReconnVM* self, const char* token) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();
  rcn_list_push(self->word_buffer, rcn_element_set_cstring(e, token));
}
const char* vm_pop_wordbuffer(ReconnVM* self) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  return rcn_element_get_cstring(rcn_list_pop(self->word_buffer, e));
}

void rcn_vm_push_value(ReconnVM* self, ReconnElement* value) {
  rcn_list_push(self->value_stack, value);
}
ReconnElement* rcn_vm_pop_value(ReconnVM* self, ReconnElement* value) {
  return rcn_list_pop(self->value_stack, value);
}

ReconnElement* rcn_vm_find_word(ReconnVM* self, const char* token) {
  char* namespace = rcn_vm_namespace(self);
  size_t namespace_length = strlen(namespace);
  size_t token_length = strlen(token);
  char* wordname = calloc(namespace_length + token_length + 1, 1);
  ReconnElement* result;

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
    result =
        rcn_dictionary_get(self->dictionaries[rcn_vm_state(self)], wordname);
    if (result) return result;
    if (!namespace[0]) break;
    rcn_seplob(namespace, '.');
  }
  return NULL;
}

int rcn_vm_do(ReconnVM* self, const char* token) {
  // static ReconnElement* e;
  // if (!e) e = newReconnElement();

  // FIXME - comb for memory leaks
  ReconnElement* e = rcn_newReconnElement();

  // fprintf(stderr, " - do >%s< inside >%d<\n", token, (int)vm_state(self));

  if (strcmp("(", token) == 0)
    self->comment++;
  else if (strcmp(")", token) == 0) {
    self->comment--;
    // assert(self->comment >= 0);
    rcn_error(self->comment >= 0, "unbalanced comments");
  }
  if (self->comment) return 0;

  int state = rcn_vm_state(self);
  switch (state) {
    case RECONN_STATE_NORMAL:
      // fprintf(stderr, " - inside NORMAL\n");
      e = rcn_vm_find_word(self, token);
      if (e) {
        // if (dictionary_has_key(self->dictionaries[RECONN_STATE_NORMAL],
        // token)) {
        //  e = dictionary_get(self->dictionaries[RECONN_STATE_NORMAL], token);
        if (e->kind == RECONN_ELEMENT_WORD_PRIMARY) {
          // fprintf(stderr, " - found prime\n");
          rcn_element_get_pword(e)(self);
        } else if (e->kind == RECONN_ELEMENT_WORD_SECONDARY) {
          // fprintf(stderr, " - found secondary\n");
          ReconnList* words = rcn_element_get_sword(e);
          for (unsigned long i = 0; i < words->top; i++) {
            e = rcn_list_get_at(words, words->top - i);
            // assert(e->kind == RECONN_ELEMENT_CSTRING);
            rcn_error(e->kind == RECONN_ELEMENT_CSTRING,
                      "non-cstring in secondary word");
            rcn_list_push(self->run_stack, e);
          }
        } else {
          rcn_error(0, "non-word in dictionary");
        }
      } else {
        ReconnElement* element = rcn_ducktype_as_whatever(token, self->base);
        if (element) {
          switch (element->kind) {
            case RECONN_ELEMENT_CSTRING:
              // element_set_bignum(
              //    element, bignum_copy_cstring(element_get_cstring(element)));
              rcn_vm_push_value(self, element);
              return 0;
              break;

              // case RECONN_ELEMENT_BIGNUM:
              //  vm_push_value(self, element);
              //  return 0;
              //  break;

            case RECONN_ELEMENT_I8:
            case RECONN_ELEMENT_I16:
            case RECONN_ELEMENT_I32:
            case RECONN_ELEMENT_U8:
            case RECONN_ELEMENT_U16:
            case RECONN_ELEMENT_U32:
              rcn_vm_push_value(self, element);
              return 0;
              break;

            default:
              rcn_error(0, "value resolved to invalid type");
              break;
          }
        } else {
          fprintf(stderr, " ! no idea what >%s< means\n", token);
        }
        return 1;
      }
      break;

    case RECONN_STATE_COMPILE:
      // fprintf(stderr, " - inside COMPILE\n");
      if (rcn_dictionary_has_key(self->dictionaries[RECONN_STATE_COMPILE],
                                 token)) {
        e = rcn_dictionary_get(self->dictionaries[RECONN_STATE_COMPILE], token);
        // assert(e->kind == RECONN_ELEMENT_WORD_PRIMARY);
        rcn_error(e->kind == RECONN_ELEMENT_WORD_PRIMARY,
                  "tried to call non-primary from dictionary");
        rcn_element_get_pword(e)(self);
      } else {
        rcn_list_push(self->word_buffer, rcn_element_set_cstring(e, token));
      }
      break;

    case RECONN_STATE_HARD:
      // fprintf(stderr, " - inside HARD COMPILE\n");
      if (strcmp(TOKEN_END, token) == 0) {
        rcn_vm_push_wordbuffer(self, TOKEN_END);
        rcn_vm_pop_state(self);
      } else {
        rcn_list_push(self->word_buffer, rcn_element_set_cstring(e, token));
      }
      break;

    default:
      break;
  }
  return 0;
}

int rcn_vm_run(ReconnVM* self) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();
  while (!rcn_list_is_empty(self->run_stack)) {
    rcn_list_pop(self->run_stack, e);
    if (e->kind == RECONN_ELEMENT_CSTRING) {
      if (rcn_vm_do(self, rcn_element_get_cstring(e))) return 1;
      ;
    }
  }
  return 0;
}

int rcn_vm_execute(ReconnVM* self, const char* word) {
  int r;
  r = rcn_vm_do(self, word);
  // FIXME refine, doesn't care abour half compiled words
  if (r) {
    self->run_stack->top = 0;
    return r;
  }
  r = rcn_vm_run(self);
  if (r) {
    self->run_stack->top = 0;
    return r;
  }
  return 0;
}

int rcn_vm_execute_all(ReconnVM* self, ReconnList* words, int ok) {
  for (unsigned long i = 1; i <= words->top; i++) {
    if (rcn_vm_execute(self,
                       rcn_element_get_cstring(rcn_list_get_at(words, i)))) {
      if (ok) fprintf(stderr, " ! ERR\n");
      return 1;
    }
  }
  if (ok) fprintf(stderr, " - OK\n");
  return 0;
}
