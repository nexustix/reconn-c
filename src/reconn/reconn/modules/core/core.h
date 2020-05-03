#ifndef RECONN_MODULES_CORE_CORE_H
#define RECONN_MODULES_CORE_CORE_H

// FIXME turn into a list of strings
static char* core_content_root;

#include <stdio.h>
#include <stdlib.h>

#include "../arithmetic/arithmetic.h"
#include "../comparison/comparison.h"
#include "../flow/flow.h"
#include "../io/io.h"
#include "../stack/stack.h"
#include "../var/var.h"
#include "reconn/parse.h"
#include "reconn/vm.h"

int core_word_def(ReconnVM* vm) {
  rcn_vm_push_state(vm, RECONN_STATE_COMPILE);
  return 0;
}

int core_word_def_compile(ReconnVM* vm) {
  rcn_vm_push_state(vm, RECONN_STATE_HARD);
  rcn_vm_push_wordbuffer(vm, TOKEN_DEF);
  return 0;
}

// TODO compile words into lists of function pointers instead of strings
int core_word_end_compile(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  ReconnList* new_word = rcn_newReconnList(2);
  for (unsigned long i = 2; i <= vm->word_buffer->top; i++) {
    e = rcn_list_get_at(vm->word_buffer, i);
    assert(e->kind == RECONN_ELEMENT_CSTRING);
    rcn_list_push(new_word, e);
  }
  e = rcn_list_get_at(vm->word_buffer, 1);
  rcn_vm_add_secondary(vm, rcn_element_get_cstring(e), new_word);
  rcn_vm_pop_state(vm);
  vm->word_buffer->top = 0;
  return 0;
}

int core_word_lambda(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  ReconnList* new_word = rcn_newReconnList(2);
  for (unsigned long i = 2; i <= vm->word_buffer->top; i++) {
    e = rcn_list_get_at(vm->word_buffer, i);
    assert(e->kind == RECONN_ELEMENT_CSTRING);
    rcn_list_push(new_word, e);
  }
  e = rcn_list_get_at(vm->word_buffer, 1);
  rcn_vm_add_secondary(vm, rcn_element_get_cstring(e), new_word);
  rcn_vm_pop_state(vm);
  rcn_vm_push_value(vm, e);
  vm->word_buffer->top = 0;
  return 0;
}

int core_word_enter(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();
  rcn_vm_pop_value(vm, e);
  assert(e->kind == RECONN_ELEMENT_CSTRING);
  rcn_vm_push_namespace(vm, rcn_element_get_cstring(e));
  return 0;
}

int core_word_leave(ReconnVM* vm) {
  rcn_vm_pop_namespace(vm);
  return 0;
}

// FIXME only a placehoder, does not do the correct thing right now
int core_word_namespace(ReconnVM* vm) {
  printf(">%s<\n", rcn_vm_namespace(vm));
  return 1;
}

// int core_word_plugin(){}

int core_word_use(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  rcn_vm_pop_value(vm, e);
  // assert(e->kind == RECONN_ELEMENT_BIGNUM);
  // const char *use_name = bignum_to_cstring(element_get_bignum(e));
  assert(e->kind == RECONN_ELEMENT_CSTRING);
  const char* use_name = rcn_element_get_cstring(e);

  // if (use_name == "io") {
  if (0) {
  } else if (strcmp(use_name, "io") == 0) {
    io_register_all(vm);
    //} else if (strcmp(use_name, "string") == 0) {
    //} else if (strcmp(use_name, "memory") == 0) {
  } else if (strcmp(use_name, "stack") == 0) {
    stack_register_all(vm);
  } else if (strcmp(use_name, "comparison") == 0) {
    comparison_register_all(vm);
  } else if (strcmp(use_name, "var") == 0) {
    var_register_all(vm);
  } else if (strcmp(use_name, "flow") == 0) {
    flow_register_all(vm);
  } else if (strcmp(use_name, "arithmetic") == 0) {
    arithmetic_register_all(vm);
    //} else if (strcmp(use_name, "file") == 0) {
    // } else if (strcmp(use_name, "") == 0) {

  } else {
    fprintf(stderr, "<!> unable to find core module >%s<\n", use_name);
    exit(1);
  }
  return RECONN_ERROR_SUCCESS;
}

int core_word_useonly(ReconnVM* vm) { return 1; }

// HACK only includes based on a single path
int core_word_include(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  rcn_vm_pop_value(vm, e);
  assert(e->kind == RECONN_ELEMENT_CSTRING);
  const char* sub_path = rcn_element_get_cstring(e);

  size_t content_root_length = strlen(core_content_root);
  size_t sub_path_length = strlen(core_content_root);

  char* complete_path = (char*)calloc(
      content_root_length + sub_path_length + strlen(".rcn") + 3, 1);

  strcat(complete_path, core_content_root);
  strcat(complete_path, "/");
  strcat(complete_path, sub_path);
  strcat(complete_path, ".rcn");

  ReconnList* tokens = rcn_newReconnList(16);
  FILE* handle = NULL;
  size_t size;
  char* data = (char*)malloc(1024);
  size_t tbd;

  handle = fopen(complete_path, "r");

  if (handle) {
    int firstline = 1;
    while ((tbd = getline(&data, &size, handle)) != -1) {
      if (firstline) {
        firstline = 0;
        // shebang support
        if (strncmp(data, "#!", strlen("#!")) == 0) {
          continue;
        }
      }
      rcn_parse_tokens(data, tokens);
      rcn_vm_execute_all(vm, tokens, 0);
      tokens->top = 0;
    }
    fclose(handle);
  }
  return RECONN_ERROR_SUCCESS;
}

int core_word_words(ReconnVM* vm) { return 1; }

int core_word_stack(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();

  unsigned long index = 0;
  printf(" <%lu> ", vm->value_stack->top);
  for (unsigned long i = 0; i < vm->value_stack->top; i++) {
    index = vm->value_stack->top - i;
    e = rcn_list_get_at(vm->value_stack, index);
    const char* kind = rcn_element_kind_to_cstring(e);
    const char* data = rcn_element_data_to_cstring(e);
    printf("(%s)[%s] ", kind, data);
    free(kind);
    free(data);
  }
  printf("\n");
  return RECONN_ERROR_SUCCESS;
}

int core_word_top(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();
  e = rcn_list_get_at(vm->value_stack, vm->value_stack->top);
  const char* kind = rcn_element_kind_to_cstring(e);
  const char* data = rcn_element_data_to_cstring(e);
  printf(" (%s)[%s]\n", kind, data);
  free(kind);
  free(data);
  return RECONN_ERROR_SUCCESS;
}

// int core_word_quote(){}

int core_word_do(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();
  rcn_vm_pop_value(vm, e);
  assert(e->kind == RECONN_ELEMENT_CSTRING);
  rcn_vm_push_run(vm, e);
  return RECONN_ERROR_SUCCESS;
}

int core_register_all(ReconnVM* vm) {
  // rcn_vm_add_primary(vm, "", core_word_);

  rcn_vm_add_primary(vm, "def", core_word_def);
  rcn_vm_add_compile(vm, "def", core_word_def_compile);
  rcn_vm_add_compile(vm, "end", core_word_end_compile);
  rcn_vm_add_compile(vm, "lambda", core_word_lambda);

  rcn_vm_add_primary(vm, "#enter", core_word_enter);
  rcn_vm_add_primary(vm, "#leave", core_word_leave);
  rcn_vm_add_primary(vm, "#namespace", core_word_namespace);

  // rcn_vm_add_primary(vm, "#plugin", core_word_);
  rcn_vm_add_primary(vm, "#use", core_word_use);
  // rcn_vm_add_primary(vm, "#useonly", core_word_);
  rcn_vm_add_primary(vm, "#include", core_word_include);

  // rcn_vm_add_primary(vm, "#words", core_word_);
  rcn_vm_add_primary(vm, "#stack", core_word_stack);
  rcn_vm_add_primary(vm, "#top", core_word_top);

  // rcn_vm_add_primary(vm, "#quote", core_word_);
  rcn_vm_add_primary(vm, "#do", core_word_do);

  // rcn_vm_add_primary(vm, "#break", core_word_);

  return RECONN_ERROR_SUCCESS;
}
int core_register_single(ReconnVM* vm, const char* name) {
  return RECONN_ERROR_NOT_IMPLEMENTED;
}

#endif