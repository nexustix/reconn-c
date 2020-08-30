#ifndef RECONN_MODULES_STACK_H
#define RECONN_MODULES_STACK_H

#include "../data/buffer.h"
#include "../vm.h"

int reconn_mod_stack_drop(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  reconn_buffer_drop(&vm->value_stack);
  return 0;
}

int reconn_mod_stack_dup(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  reconn_buffer_dup(&vm->value_stack);
  return 0;
}

int reconn_mod_stack_swap(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 1)) {
    vm->got_error = 1;
    return -1;
  }
  reconn_buffer_swap(&vm->value_stack);
  return 0;
}

int reconn_mod_stack_over(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 1)) {
    vm->got_error = 1;
    return -1;
  }
  reconn_buffer_over(&vm->value_stack);
  return 0;
}

// FIXME lacks propper error checking
int reconn_mod_stack_dig(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 1)) {
    vm->got_error = 1;
    return -1;
  }
  ReconnValueKind ckind = reconn_buffer_kind_at(&vm->value_stack, -1);
  const void *cvalue = reconn_buffer_pop_void(&vm->value_stack);
  long long count = reconn_value_to_s64(ckind, cvalue);

  for (long long i = 0; i < count; i++) {
    reconn_buffer_transfer(&vm->run_stack, &vm->value_stack);
  }

  ReconnValueKind kind = reconn_buffer_kind_at(&vm->value_stack, -1);
  size_t size = reconn_buffer_size_at(&vm->value_stack, -1);
  const void *tmp_value = reconn_buffer_pop_void(&vm->value_stack);
  // reconn_buffer_pop_void(&vm->value_stack);
  void *value = malloc(size);
  memcpy(value, tmp_value, size);

  for (long long i = 0; i < count; i++) {
    reconn_buffer_transfer(&vm->value_stack, &vm->run_stack);
  }

  reconn_buffer_push_void(&vm->value_stack, value, size, kind);

  // reconn_buffer_over(&vm->value_stack);
  free(value);
  return 0;
}

// FIXME lacks propper error checking
int reconn_mod_stack_burry(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 1)) {
    vm->got_error = 1;
    return -1;
  }
  ReconnValueKind ckind = reconn_buffer_kind_at(&vm->value_stack, -1);
  const void *cvalue = reconn_buffer_pop_void(&vm->value_stack);
  long long count = reconn_value_to_s64(ckind, cvalue);

  ReconnValueKind kind = reconn_buffer_kind_at(&vm->value_stack, -1);
  size_t size = reconn_buffer_size_at(&vm->value_stack, -1);
  const void *tmp_value = reconn_buffer_pop_void(&vm->value_stack);
  void *value = malloc(size);
  memcpy(value, tmp_value, size);

  for (long long i = 0; i < count; i++) {
    reconn_buffer_transfer(&vm->run_stack, &vm->value_stack);
  }

  reconn_buffer_push_void(&vm->value_stack, value, size, kind);

  for (long long i = 0; i < count; i++) {
    reconn_buffer_transfer(&vm->value_stack, &vm->run_stack);
  }

  free(value);
  // reconn_buffer_over(&vm->value_stack);
  return 0;
}

int reconn_mod_stack_register_all(ReconnVM *vm) {
  reconn_vm_add_primary(vm, "drop", reconn_mod_stack_drop);
  reconn_vm_add_primary(vm, "dup", reconn_mod_stack_dup);
  reconn_vm_add_primary(vm, "swap", reconn_mod_stack_swap);
  reconn_vm_add_primary(vm, "over", reconn_mod_stack_over);
  // reconn_vm_add_primary(vm, "rot", reconn_mod_stack_rot);
  reconn_vm_add_primary(vm, "dig", reconn_mod_stack_dig);
  reconn_vm_add_primary(vm, "burry", reconn_mod_stack_burry);

  return 0;
}
#endif