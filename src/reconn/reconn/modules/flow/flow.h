#ifndef RECONN_MODULES_FLOW_FLOW_H
#define RECONN_MODULES_FLOW_FLOW_H

#include "reconn/vm.h"

int flow_word_if(ReconnVM* vm) {
  ReconnElement* no = rcn_newReconnElement();
  ReconnElement* yes = rcn_newReconnElement();
  ReconnElement* value = rcn_newReconnElement();

  rcn_vm_pop_value(vm, no);
  rcn_vm_pop_value(vm, yes);
  rcn_vm_pop_value(vm, value);

  assert(no->kind == RECONN_ELEMENT_CSTRING);
  assert(yes->kind == RECONN_ELEMENT_CSTRING);
  assert(rcn_element_is_integer(value));

  if (rcn_element_to_boolean(value)) {
    rcn_vm_push_run(vm, yes);
  } else {
    rcn_vm_push_run(vm, no);
  }

  free(no);
  free(yes);
  free(value);

  return RECONN_ERROR_SUCCESS;
}
int flow_word_when(ReconnVM* vm) {
  ReconnElement* yes = rcn_newReconnElement();
  ReconnElement* value = rcn_newReconnElement();

  rcn_vm_pop_value(vm, yes);
  rcn_vm_pop_value(vm, value);

  assert(yes->kind == RECONN_ELEMENT_CSTRING);
  assert(rcn_element_is_integer(value));

  if (rcn_element_to_boolean(value)) {
    rcn_vm_push_run(vm, yes);
  }

  free(yes);
  free(value);
  return RECONN_ERROR_SUCCESS;
}

int flow_register_all(ReconnVM* vm) {
  rcn_vm_add_primary(vm, "if", flow_word_if);
  rcn_vm_add_primary(vm, "when", flow_word_when);
  return RECONN_ERROR_SUCCESS;
}

int flow_register_single(ReconnVM* vm, const char* name) {
  return RECONN_ERROR_NOT_IMPLEMENTED;
}

#endif