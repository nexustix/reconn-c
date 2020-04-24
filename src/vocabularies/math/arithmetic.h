#ifndef VOCABULARIES_MATH_ARITMETIC_H
#define VOCABULARIES_MATH_ARITMETIC_H

#include "../../bignum.h"
#include "../../element.h"
#include "../../vm.h"

void voc_mat_add(VM *vm) {
  Element *eb = vm_pop_value(vm, newElement());
  Element *ea = vm_pop_value(vm, newElement());
  static Element *er;
  if (!er) er = newElement();

  assert(ea->kind == ELEMENT_BIGNUM);
  assert(eb->kind == ELEMENT_BIGNUM);

  Bignum *a = element_get_bignum(ea);
  Bignum *b = element_get_bignum(eb);
  Bignum *r = newBignum(10);

  bignum_add(r, a, b);

  vm_push_value(vm, element_set_bignum(er, r));

  free(a);
  free(b);
}

void voc_mat_sub(VM *vm) {
  Element *eb = vm_pop_value(vm, newElement());
  Element *ea = vm_pop_value(vm, newElement());
  static Element *er;
  if (!er) er = newElement();

  assert(ea->kind == ELEMENT_BIGNUM);
  assert(eb->kind == ELEMENT_BIGNUM);

  Bignum *a = element_get_bignum(ea);
  Bignum *b = element_get_bignum(eb);
  Bignum *r = newBignum(10);

  bignum_sub(r, a, b);

  vm_push_value(vm, element_set_bignum(er, r));

  free(a);
  free(b);
}

void voc_mat_register_words(VM *vm) {
  // vm_add_primary(vm, "add", voc_mat_ari_add);
  // vm_add_primary(vm, "sub", voc_mat_ari_sub);
  vm_add_primary(vm, "+", voc_mat_add);
  vm_add_primary(vm, "-", voc_mat_sub);
}

#endif