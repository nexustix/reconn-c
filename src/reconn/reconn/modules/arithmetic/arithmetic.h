#ifndef RECONN_MODULE_ARITHMETIC_ARITHMETIC_H
#define RECONN_MODULE_ARITHMETIC_ARITHMETIC_H

#include <inttypes.h>

#include "reconn/error.h"
#include "reconn/vm.h"

int arithmetic_word_add(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();
  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a));
  assert(rcn_element_is_integer(b));

  if (rcn_element_is_signed_integer(a) || rcn_element_is_signed_integer(b)) {
    long na = rcn_element_take_i32(a, 0);
    long nb = rcn_element_take_i32(b, 0);
    long* nr = (long*)malloc(sizeof(long));
    *nr = na + nb;
    rcn_element_set_i32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);

  } else {
    unsigned long na = rcn_element_take_u32(a, 0);
    unsigned long nb = rcn_element_take_u32(b, 0);
    unsigned long* nr = (unsigned long*)malloc(sizeof(unsigned long));
    *nr = na + nb;
    rcn_element_set_u32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);
  }

  free(a);
  free(b);

  return RECONN_ERROR_SUCCESS;
}

int arithmetic_word_sub(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();
  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a));
  assert(rcn_element_is_integer(b));

  if (rcn_element_is_signed_integer(a) || rcn_element_is_signed_integer(b)) {
    long na = rcn_element_take_i32(a, 0);
    long nb = rcn_element_take_i32(b, 0);
    long* nr = (long*)malloc(sizeof(long));
    *nr = na - nb;
    rcn_element_set_i32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);

  } else {
    unsigned long na = rcn_element_take_u32(a, 0);
    unsigned long nb = rcn_element_take_u32(b, 0);
    unsigned long* nr = (unsigned long*)malloc(sizeof(unsigned long));
    *nr = na - nb;
    rcn_element_set_u32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);
  }

  free(a);
  free(b);

  return RECONN_ERROR_SUCCESS;
}

int arithmetic_word_mul(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();
  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a));
  assert(rcn_element_is_integer(b));

  if (rcn_element_is_signed_integer(a) || rcn_element_is_signed_integer(b)) {
    long na = rcn_element_take_i32(a, 0);
    long nb = rcn_element_take_i32(b, 0);
    long* nr = (long*)malloc(sizeof(long));
    *nr = na * nb;
    rcn_element_set_i32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);

  } else {
    unsigned long na = rcn_element_take_u32(a, 0);
    unsigned long nb = rcn_element_take_u32(b, 0);
    unsigned long* nr = (unsigned long*)malloc(sizeof(unsigned long));
    *nr = na * nb;
    rcn_element_set_u32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);
  }

  free(a);
  free(b);

  return RECONN_ERROR_SUCCESS;
}

int arithmetic_word_idiv(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();
  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a));
  assert(rcn_element_is_integer(b));

  if (rcn_element_is_signed_integer(a) || rcn_element_is_signed_integer(b)) {
    long na = rcn_element_take_i32(a, 0);
    long nb = rcn_element_take_i32(b, 0);
    long* nr = (long*)malloc(sizeof(long));
    *nr = na / nb;
    rcn_element_set_i32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);
  } else {
    unsigned long na = rcn_element_take_u32(a, 0);
    unsigned long nb = rcn_element_take_u32(b, 0);
    unsigned long* nr = (unsigned long*)malloc(sizeof(unsigned long));
    *nr = na / nb;
    rcn_element_set_u32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);
  }

  free(a);
  free(b);

  return RECONN_ERROR_SUCCESS;
}
int arithmetic_word_div(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();
  ReconnElement* r2 = rcn_newReconnElement();
  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a));
  assert(rcn_element_is_integer(b));

  if (rcn_element_is_signed_integer(a) || rcn_element_is_signed_integer(b)) {
    long na = rcn_element_take_i32(a, 0);
    long nb = rcn_element_take_i32(b, 0);
    long* nr = (long*)malloc(sizeof(long));
    long* nr2 = (long*)malloc(sizeof(long));
    *nr = na / nb;
    *nr2 = na % nb;
    rcn_element_set_i32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);
    free(r2);
  } else {
    unsigned long na = rcn_element_take_u32(a, 0);
    unsigned long nb = rcn_element_take_u32(b, 0);
    unsigned long* nr = (unsigned long*)malloc(sizeof(unsigned long));
    unsigned long* nr2 = (unsigned long*)malloc(sizeof(unsigned long));
    *nr = na / nb;
    *nr2 = na % nb;
    rcn_element_set_u32(r, nr);
    rcn_element_set_u32(r2, nr2);
    rcn_vm_push_value(vm, r);
    rcn_vm_push_value(vm, r2);

    free(r);
    free(r2);
  }

  free(a);
  free(b);

  return RECONN_ERROR_SUCCESS;
}

int arithmetic_word_mod(ReconnVM* vm) {
  ReconnElement* b = rcn_newReconnElement();
  ReconnElement* a = rcn_newReconnElement();
  ReconnElement* r = rcn_newReconnElement();
  rcn_vm_pop_value(vm, b);
  rcn_vm_pop_value(vm, a);

  assert(rcn_element_is_integer(a));
  assert(rcn_element_is_integer(b));

  if (rcn_element_is_signed_integer(a) || rcn_element_is_signed_integer(b)) {
    long na = rcn_element_take_i32(a, 0);
    long nb = rcn_element_take_i32(b, 0);
    long* nr = (long*)malloc(sizeof(long));
    *nr = na % nb;
    rcn_element_set_i32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);

  } else {
    unsigned long na = rcn_element_take_u32(a, 0);
    unsigned long nb = rcn_element_take_u32(b, 0);
    unsigned long* nr = (unsigned long*)malloc(sizeof(unsigned long));
    *nr = na % nb;
    rcn_element_set_u32(r, nr);
    rcn_vm_push_value(vm, r);

    free(r);
  }

  free(a);
  free(b);
  // free(r);

  return RECONN_ERROR_SUCCESS;
}

int arithmetic_register_all(ReconnVM* vm) {
  rcn_vm_add_primary(vm, "+", arithmetic_word_add);
  rcn_vm_add_primary(vm, "-", arithmetic_word_sub);
  rcn_vm_add_primary(vm, "*", arithmetic_word_mul);
  rcn_vm_add_primary(vm, "//", arithmetic_word_idiv);
  rcn_vm_add_primary(vm, "/", arithmetic_word_div);
  rcn_vm_add_primary(vm, "%", arithmetic_word_mod);
  return RECONN_ERROR_SUCCESS;
}

int arithmetic_register_single(ReconnVM* vm, const char* name) {
  return RECONN_ERROR_NOT_IMPLEMENTED;
}

#endif