#ifndef RECONN_MODULES_STACK_STACK_H
#define RECONN_MODULES_STACK_STACK_H

#include <stdio.h>

#include "reconn/data/element.h"
#include "reconn/error.h"
#include "reconn/vm.h"

int stack_word_swap(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();

  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  rcn_vm_push_value(vm, b);
  rcn_vm_push_value(vm, a);

  free(b);
  free(a);
  return RECONN_ERROR_SUCCESS;
}

int stack_word_over(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();

  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  rcn_vm_push_value(vm, a);
  rcn_vm_push_value(vm, b);
  rcn_vm_push_value(vm, a);

  free(b);
  free(a);
  return RECONN_ERROR_SUCCESS;
}

int stack_word_dup(ReconnVM* vm) {
  ReconnElement* a = rcn_newReconnElement();

  rcn_vm_pop_value(vm, a);

  rcn_vm_push_value(vm, a);
  rcn_vm_push_value(vm, a);

  free(a);
  return RECONN_ERROR_NOT_IMPLEMENTED;
}

int stack_word_drop(ReconnVM* vm) {
  ReconnElement* a = rcn_newReconnElement();
  rcn_vm_pop_value(vm, a);
  free(a);
  return RECONN_ERROR_SUCCESS;
}

int stack_word_rot(ReconnVM* vm) {
  ReconnElement* c = rcn_newReconnElement();
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();

  rcn_vm_pop_value(vm, c);
  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  rcn_vm_push_value(vm, c);
  rcn_vm_push_value(vm, b);
  rcn_vm_push_value(vm, a);

  free(c);
  free(b);
  free(a);
  return RECONN_ERROR_NOT_IMPLEMENTED;
}

int stack_register_all(ReconnVM* vm) {
  rcn_vm_add_primary(vm, "swap", stack_word_swap);
  rcn_vm_add_primary(vm, "over", stack_word_over);
  rcn_vm_add_primary(vm, "dup", stack_word_dup);
  rcn_vm_add_primary(vm, "drop", stack_word_drop);
  rcn_vm_add_primary(vm, "rot", stack_word_rot);
  return RECONN_ERROR_SUCCESS;
}

int stack_register_single(ReconnVM* vm, const char* name) {
  return RECONN_ERROR_NOT_IMPLEMENTED;
}

#endif