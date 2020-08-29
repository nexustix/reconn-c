#ifndef RECONN_MODULES_IO_H
#define RECONN_MODULES_IO_H

#include "../data/buffer.h"
#include "../data/ducktype.h"
#include "../vm.h"
#include <assert.h>
//#include <ctype.h>
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

/*
int reconn_mod_io_accept(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }

  const ReconnValueKind kind_a = reconn_buffer_kind_at(&vm->value_stack, -1);

  if (!(reconn_value_is_number(kind_a))) {
    vm->got_error = 1;
    return -1;
  }
  unsigned long long size =
      reconn_value_to_u64(kind_a, reconn_buffer_pop_void(&vm->value_stack));

  char *data = malloc(size + 2);
  for (unsigned long long i = 0; i <= size; i++) {
    if (i == size) {
      data[i] = 0;
    } else {
      data[i] = getchar();
    }
  }

  reconn_buffer_push_cstring(&vm->value_stack, data);

  free(data);
  return 0;
}
*/

int reconn_mod_io_acceptln(ReconnVM *vm) {
  size_t size = 0;
  char *data = NULL;
  getline(&data, &size, stdin);

  reconn_buffer_push_cstring(&vm->value_stack, data);

  free(data);
  return 0;
}

int reconn_mod_io_ducktype(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  if (!(reconn_buffer_kind_at(&vm->value_stack, -1) == RECONN_VALUE_C_STRING)) {
    vm->got_error = 1;
    return -1;
  }

  char *str = reconn_buffer_pop_cstring(&vm->value_stack);

  if (reconn_ducktype_as_whatever(&vm->value_stack, str)) {
    free(str);
    reconn_buffer_push_s8(&vm->value_stack, 1);
    return 1;
  }
  free(str);
  reconn_buffer_push_s8(&vm->value_stack, 0);
  return 0;
}

int reconn_mod_io_register_all(ReconnVM *vm) {
  reconn_vm_add_primary(vm, "print", reconn_mod_io_print);
  reconn_vm_add_primary(vm, "println", reconn_mod_io_println);
  // reconn_vm_add_primary(vm, "accept", reconn_mod_io_accept);
  reconn_vm_add_primary(vm, "inputln", reconn_mod_io_acceptln);
  reconn_vm_add_primary(vm, "ducktype", reconn_mod_io_ducktype);
  return 0;
}

#endif