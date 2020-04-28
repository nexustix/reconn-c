#ifndef RECONN_MODULES_IO_IO_H
#define RECONN_MODULES_IO_IO_H

#include "reconn/vm.h"

// int io_word_key(ReconnVM* vm) { return 1; }

// int io_word_emit(ReconnVM* vm) { return 1; }

// int io_word_print(ReconnVM* vm) { return 1; }

// int io_word_eprint(ReconnVM* vm) { return 1; }

int io_word_println(ReconnVM* vm) {
  static ReconnElement* e;
  if (!e) e = rcn_newReconnElement();
  rcn_vm_pop_value(vm, e);
  printf("%s\n", rcn_element_data_to_cstring(e));
  free(e);
  return 0;
}

// int io_word_eprintln(ReconnVM* vm) { return 1; }

// int io_word_flush(ReconnVM* vm) { return 1; }

// int io_word_eflush(ReconnVM* vm) { return 1; }

// int io_word_input(ReconnVM* vm) { return 1; }

// int io_word_inputln(ReconnVM* vm) { return 1; }

int io_register_all(ReconnVM* vm) {
  rcn_vm_add_primary(vm, "println", io_word_println);
  return 0;
}

int io_register_single(ReconnVM* vm, const char* name) { return 1; }

#endif