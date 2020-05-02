#ifndef RECONN_MODULES_COMPARISON_COMPARISON_H
#define RECONN_MODULES_COMPARISON_COMPARISON_H

#include <stdio.h>

#include "reconn/data/element.h"
#include "reconn/data/list.h"
#include "reconn/error.h"
#include "reconn/vm.h"

// int comparison_word_(ReconnVM* vm) { return RECONN_ERROR_NOT_IMPLEMENTED; }

int comparison_word_eq(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();

  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a) && rcn_element_is_integer(b));
  unsigned char* rn = (unsigned char*)calloc(1, sizeof(unsigned char));
  *rn = rcn_element_take_i64(a, 0) == rcn_element_take_i64(b, 0);
  rcn_element_set_u8(r, rn);
  rcn_vm_push_value(vm, r);

  free(b);
  free(a);
  free(r);

  return RECONN_ERROR_SUCCESS;
}

int comparison_word_gt(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();

  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a) && rcn_element_is_integer(b));
  unsigned char* rn = (unsigned char*)calloc(1, sizeof(unsigned char));
  *rn = rcn_element_take_i64(a, 0) > rcn_element_take_i64(b, 0);
  rcn_element_set_u8(r, rn);
  rcn_vm_push_value(vm, r);

  free(b);
  free(a);
  free(r);

  return RECONN_ERROR_SUCCESS;
}

int comparison_word_lt(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();

  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a) && rcn_element_is_integer(b));
  unsigned char* rn = (unsigned char*)calloc(1, sizeof(unsigned char));
  *rn = rcn_element_take_i64(a, 0) < rcn_element_take_i64(b, 0);
  rcn_element_set_u8(r, rn);
  rcn_vm_push_value(vm, r);

  free(b);
  free(a);
  free(r);

  return RECONN_ERROR_SUCCESS;
}

int comparison_word_ge(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();

  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a) && rcn_element_is_integer(b));
  unsigned char* rn = (unsigned char*)calloc(1, sizeof(unsigned char));
  *rn = rcn_element_take_i64(a, 0) >= rcn_element_take_i64(b, 0);
  rcn_element_set_u8(r, rn);
  rcn_vm_push_value(vm, r);

  free(b);
  free(a);
  free(r);

  return RECONN_ERROR_SUCCESS;
}

int comparison_word_le(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();

  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a) && rcn_element_is_integer(b));
  unsigned char* rn = (unsigned char*)calloc(1, sizeof(unsigned char));
  *rn = rcn_element_take_i64(a, 0) <= rcn_element_take_i64(b, 0);
  rcn_element_set_u8(r, rn);
  rcn_vm_push_value(vm, r);

  free(b);
  free(a);
  free(r);

  return RECONN_ERROR_SUCCESS;
}

int comparison_register_all(ReconnVM* vm) {
  // rcn_vm_add_primary(vm, "", comparison_word_);
  rcn_vm_add_primary(vm, "=", comparison_word_eq);
  rcn_vm_add_primary(vm, ">", comparison_word_gt);
  rcn_vm_add_primary(vm, "<", comparison_word_lt);
  rcn_vm_add_primary(vm, ">=", comparison_word_ge);
  rcn_vm_add_primary(vm, "<=", comparison_word_le);
  return RECONN_ERROR_SUCCESS;
}

int comparison_register_single(ReconnVM* vm, const char* name) {
  return RECONN_ERROR_NOT_IMPLEMENTED;
}

#endif