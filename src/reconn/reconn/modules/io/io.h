#ifndef RECONN_MODULES_IO_IO_H
#define RECONN_MODULES_IO_IO_H

#include "reconn/error.h"
#include "reconn/vm.h"

// int io_word_key(ReconnVM* vm) { return 1; }

// int io_word_emit(ReconnVM* vm) { return 1; }

int io_word_print(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();
  rcn_vm_pop_value(vm, e);
  printf("%s", rcn_element_data_to_cstring(e));
  free(e);
  return RECONN_ERROR_SUCCESS;
}

// int io_word_eprint(ReconnVM* vm) { return 1; }

int io_word_println(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();
  rcn_vm_pop_value(vm, e);
  printf("%s\n", rcn_element_data_to_cstring(e));
  free(e);
  return RECONN_ERROR_SUCCESS;
}

// int io_word_eprintln(ReconnVM* vm) { return 1; }

int io_word_flush(ReconnVM* vm) {
  fflush(stdout);
  return RECONN_ERROR_SUCCESS;
}

// int io_word_eflush(ReconnVM* vm) { return 1; }

// int io_word_input(ReconnVM* vm) { return 1; }

// int io_word_inputln(ReconnVM* vm) { return 1; }

int io_register_all(ReconnVM* vm) {
  rcn_vm_add_primary(vm, "print", io_word_print);
  rcn_vm_add_primary(vm, "println", io_word_println);
  rcn_vm_add_primary(vm, "flush", io_word_flush);
  return RECONN_ERROR_SUCCESS;
}

int io_register_single(ReconnVM* vm, const char* name) {
  return RECONN_ERROR_NOT_IMPLEMENTED;
}

#endif