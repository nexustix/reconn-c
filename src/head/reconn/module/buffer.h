#ifndef RECONN_MODULES_BUFFER_H
#define RECONN_MODULES_BUFFER_H

#include "../data/buffer.h"
#include "../data/value.h"
#include "../vm.h"
#include <stdint.h>
#include <stdlib.h>

int reconn_mod_buffer_new(ReconnVM *vm) {
  ReconnBuffer *buffer = (ReconnBuffer *)malloc(sizeof(ReconnBuffer));
  *buffer = reconn_makeBuffer();

  char *ptrstr = reconn_value_value_to_string(RECONN_VALUE_POINTER, buffer);

  reconn_buffer_push_cstring(&vm->compile_buffer, ptrstr);

  free(ptrstr);

  return 0;
}

int reconn_mod_buffer_free(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  if (!(reconn_value_is_number(reconn_buffer_kind_at(&vm->value_stack, -1)))) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind = reconn_buffer_kind_at(&vm->value_stack, -1);
  const void *value = reconn_buffer_pop_void(&vm->value_stack);
  ReconnBuffer *pointer = (ReconnBuffer *)reconn_value_to_u64(kind, value);
  reconn_buffer_free(pointer, 1);
  return 0;
}

int reconn_mod_buffer_push(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  if (!(reconn_value_is_number(reconn_buffer_kind_at(&vm->value_stack, -1)))) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind = reconn_buffer_kind_at(&vm->value_stack, -1);
  const void *value = reconn_buffer_pop_void(&vm->value_stack);
  ReconnBuffer *pointer = (ReconnBuffer *)reconn_value_to_u64(kind, value);
  reconn_buffer_transfer(pointer, &vm->value_stack);
  // reconn_buffer_transfer(&vm->value_stack, pointer);
  return 0;
}

int reconn_mod_buffer_pop(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  if (!(reconn_value_is_number(reconn_buffer_kind_at(&vm->value_stack, -1)))) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind = reconn_buffer_kind_at(&vm->value_stack, -1);
  const void *value = reconn_buffer_pop_void(&vm->value_stack);
  ReconnBuffer *pointer = (ReconnBuffer *)reconn_value_to_u64(kind, value);
  reconn_buffer_transfer(&vm->value_stack, pointer);
  return 0;
}

int reconn_mod_buffer_count(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  if (!(reconn_value_is_number(reconn_buffer_kind_at(&vm->value_stack, -1)))) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind = reconn_buffer_kind_at(&vm->value_stack, -1);
  const void *value = reconn_buffer_pop_void(&vm->value_stack);
  ReconnBuffer *pointer = (ReconnBuffer *)reconn_value_to_u64(kind, value);
  reconn_buffer_push_u64(&vm->value_stack, pointer->count);
  return 0;
}

int reconn_mod_buffer_get(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 1)) {
    vm->got_error = 1;
    return -1;
  }
  if (!(reconn_value_is_number(reconn_buffer_kind_at(&vm->value_stack, -1)))) {
    vm->got_error = 1;
    return -1;
  }
  if (!(reconn_value_is_number(reconn_buffer_kind_at(&vm->value_stack, -2)))) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind = reconn_buffer_kind_at(&vm->value_stack, -1);
  const void *value = reconn_buffer_pop_void(&vm->value_stack);
  ReconnBuffer *pointer = (ReconnBuffer *)reconn_value_to_u64(kind, value);

  const ReconnValueKind kind_b = reconn_buffer_kind_at(&vm->value_stack, -1);
  const void *value_b = reconn_buffer_pop_void(&vm->value_stack);
  long long index = reconn_value_to_s64(kind_b, value_b);
  // reconn_buffer_transfer(&vm->value_stack, pointer);
  reconn_buffer_copy(&vm->value_stack, index, pointer);
  return 0;
}

int reconn_mod_buffer_print(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  if (!(reconn_value_is_number(reconn_buffer_kind_at(&vm->value_stack, -1)))) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind = reconn_buffer_kind_at(&vm->value_stack, -1);
  const void *value = reconn_buffer_pop_void(&vm->value_stack);
  ReconnBuffer *pointer = (ReconnBuffer *)reconn_value_to_u64(kind, value);
  // reconn_buffer_transfer(&vm->value_stack, pointer);
  reconn_buffer_pprint(pointer);
  return 0;
}

int reconn_mod_buffer_register_all(ReconnVM *vm) {

  reconn_vm_add_primary(vm, "newBuffer", reconn_mod_buffer_new);
  reconn_vm_add_primary(vm, "freeBuffer", reconn_mod_buffer_free);
  reconn_vm_add_primary(vm, "freeBuffer", reconn_mod_buffer_free);
  reconn_vm_add_primary(vm, "b<", reconn_mod_buffer_push);
  reconn_vm_add_primary(vm, "b>", reconn_mod_buffer_pop);
  reconn_vm_add_primary(vm, "b#", reconn_mod_buffer_count);
  reconn_vm_add_primary(vm, "b@", reconn_mod_buffer_get);
  reconn_vm_add_primary(vm, "b?", reconn_mod_buffer_print);

  return 0;
}

#endif