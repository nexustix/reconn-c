#ifndef RECONN_MODULES_IO_H
#define RECONN_MODULES_IO_H

#include "../data/buffer.h"
#include "../vm.h"
#include <assert.h>
#include <stdio.h>

int reconn_mod_io_print(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  ReconnValueKind kind =
      reconn_buffer_kind_at(&vm->value_stack, vm->value_stack.lasti);
  void *thing = reconn_buffer_pop_cstring(&vm->value_stack);
  char *rep = reconn_value_value_to_string(kind, thing);
  printf("%s", rep);
  free(thing);
  free(rep);
  return 0;
}

int reconn_mod_io_println(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  ReconnValueKind kind =
      reconn_buffer_kind_at(&vm->value_stack, vm->value_stack.lasti);
  void *thing = reconn_buffer_pop_cstring(&vm->value_stack);
  char *rep = reconn_value_value_to_string(kind, thing);
  printf("%s\n", rep);
  free(thing);
  free(rep);
  return 0;
}

int reconn_mod_io_register_all(ReconnVM *vm) {
  reconn_vm_add_primary(vm, "print", reconn_mod_io_print);
  reconn_vm_add_primary(vm, "println", reconn_mod_io_println);
  return 0;
}

#endif