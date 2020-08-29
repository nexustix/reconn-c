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

int reconn_mod_stack_register_all(ReconnVM *vm) {
  reconn_vm_add_primary(vm, "drop", reconn_mod_stack_drop);
  reconn_vm_add_primary(vm, "dup", reconn_mod_stack_dup);
  reconn_vm_add_primary(vm, "swap", reconn_mod_stack_swap);
  reconn_vm_add_primary(vm, "over", reconn_mod_stack_over);
  return 0;
}
#endif