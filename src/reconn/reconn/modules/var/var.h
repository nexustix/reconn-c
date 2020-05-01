#ifndef RECONN_MODULES_VAR_VAR_H
#define RECONN_MODULES_VAR_VAR_H

#include <stdio.h>

#include "reconn/data/element.h"
#include "reconn/data/list.h"
#include "reconn/error.h"
#include "reconn/vm.h"

static ReconnList* var_variables;

void var_init() {
  if (!var_variables) var_variables = rcn_newReconnList(8);
}

int var_word_var(ReconnVM* vm) {
  ReconnElement* data_element = rcn_newReconnElement();
  data_element->kind = RECONN_ELEMENT_RESERVED;
  unsigned long ptr = rcn_list_insert(var_variables, data_element);

  char* dat = (char*)calloc(10 + 1, sizeof(char));
  sprintf(dat, "%lu", ptr);
  rcn_vm_push_wordbuffer(vm, dat);

  return RECONN_ERROR_SUCCESS;
}
int var_word_set(ReconnVM* vm) {
  ReconnElement* ptr = rcn_newReconnElement();
  ReconnElement* val = rcn_newReconnElement();
  rcn_vm_pop_value(vm, ptr);
  rcn_vm_pop_value(vm, val);

  rcn_list_set_at(var_variables, rcn_element_take_u32(ptr, 0), val);

  free(ptr);
  free(val);

  return RECONN_ERROR_SUCCESS;
}
int var_word_get(ReconnVM* vm) {
  ReconnElement* ptr = rcn_newReconnElement();
  // ReconnElement* val = rcn_newReconnElement();
  rcn_vm_pop_value(vm, ptr);

  ReconnElement* val =
      rcn_list_get_at(var_variables, rcn_element_take_u32(ptr, 0));
  rcn_vm_push_value(vm, val);

  free(ptr);
  // free(val);
  return RECONN_ERROR_SUCCESS;
}
int var_word_del(ReconnVM* vm) { return RECONN_ERROR_NOT_IMPLEMENTED; }

int var_register_all(ReconnVM* vm) {
  var_init();
  rcn_vm_add_compile(vm, "var", var_word_var);
  rcn_vm_add_primary(vm, "vset", var_word_set);
  rcn_vm_add_primary(vm, "vget", var_word_get);
  // rcn_vm_add_primary(vm, "del", var_word_del);
  return RECONN_ERROR_SUCCESS;
}

int var_register_single(ReconnVM* vm, const char* name) {
  var_init();
  return RECONN_ERROR_NOT_IMPLEMENTED;
}

#endif