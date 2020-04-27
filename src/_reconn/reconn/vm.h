#ifndef RECONN_VM_H
#define RECONN_VM_H
#include <string.h>

#include "data/dictionary.h"
#include "data/element.h"
#include "data/list.h"
#include "ducktype.h"
#include "util.h"

#define TOKEN_DEF "def"
#define TOKEN_END "end"

typedef enum ReconnStateKind {
  RECONN_STATE_NORMAL,
  RECONN_STATE_COMPILE,
  RECONN_STATE_HARD,
  RECONN_STATE_COUNT,
} ReconnStateKind;

typedef enum ReconnWordKind {
  RECONN_WORD_PRIMARY,
  RECONN_WORD_SECONDARY,
  RECONN_WORD_COMPILE,
} ReconnWordKind;

typedef struct ReconnVM {
  ReconnList* run_stack;
  ReconnList* value_stack;
  ReconnList* state_stack;
  ReconnList* namespace_stack;

  ReconnDictionary** dictionaries;

  ReconnList* word_buffer;

  int comment;
  int running;

  int base;
} ReconnVM;

int (*rcn_element_get_pword(ReconnElement* self))(ReconnVM*);

ReconnElement* rcn_element_set_pword(ReconnElement* destination,
                                     int (*source)(ReconnVM*));

ReconnList* rcn_element_get_sword(ReconnElement* self);

ReconnElement* rcn_element_set_sword(ReconnElement* destination,
                                     ReconnList* source);

ReconnVM* rcn_newReconnVM();

ReconnStateKind rcn_vm_state(ReconnVM* self);

void rcn_vm_push_state(ReconnVM* self, ReconnStateKind state);

ReconnStateKind rcn_vm_pop_state(ReconnVM* self);

char* rcn_vm_namespace(ReconnVM* self);

void rcn_vm_push_namespace(ReconnVM* self, const char* name);

const char* rcn_vm_pop_namespace(ReconnVM* self);

const char* rcn_vm_spacename(ReconnVM* self, const char* token);

void rcn_vm_add_primary(ReconnVM* self, const char* token,
                        int (*callback)(ReconnVM*));

void rcn_vm_add_secondary(ReconnVM* self, const char* token,
                          ReconnList* source);

void rcn_vm_add_compile(ReconnVM* self, const char* token,
                        int (*callback)(ReconnVM*));

void rcn_vm_push_wordbuffer(ReconnVM* self, const char* token);
const char* rcn_vm_pop_wordbuffer(ReconnVM* self);

void rcn_vm_push_value(ReconnVM* self, ReconnElement* value);
ReconnElement* rcn_vm_pop_value(ReconnVM* self, ReconnElement* value);

ReconnElement* rcn_vm_find_word(ReconnVM* self, const char* token);

int rcn_vm_do(ReconnVM* self, const char* token);

int rcn_vm_run(ReconnVM* self);

int rcn_vm_execute(ReconnVM* self, const char* word);

int rcn_vm_execute_all(ReconnVM* self, ReconnList* words, int ok);

#endif