#ifndef RECONN_MODULES_CORE_H
#define RECONN_MODULES_CORE_H

#include "../data/buffer.h"
#include "../util.h"
#include "../vm.h"
#include <assert.h>

int reconn_mod_core_pstart_wipe(ReconnVM *vm) {
  vm->compile = 1;
  reconn_buffer_reset(&vm->compile_buffer);
  return 0;
}

int reconn_mod_core_pstart(ReconnVM *vm) {
  vm->compile = 1;
  return 0;
}

int reconn_mod_core_cstop(ReconnVM *vm) {
  vm->compile = 0;
  return 0;
}

int reconn_mod_core_pdef(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  char *name = reconn_buffer_pop_cstring(&vm->value_stack);
  reconn_vm_add_secondary(vm, name);
  vm->compile = 0;
  free(name);
  return 0;
}

int reconn_mod_core_pstack(ReconnVM *vm) {
  // reconn_buffer_print(&vm->value_stack);
  reconn_buffer_pprint(&vm->value_stack);
  return 0;
}

int reconn_mod_core_pdstack(ReconnVM *vm) {
  // reconn_buffer_print(&vm->value_stack);
  reconn_buffer_print(&vm->value_stack);
  return 0;
}

int reconn_mod_core_pstop(ReconnVM *vm) {
  vm->running = 0;
  return 0;
}

int reconn_mod_core_penter(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  char *name = reconn_buffer_pop_cstring(&vm->value_stack);
  reconn_vm_enter_namespace(vm, name);
  free(name);
  return 0;
}

int reconn_mod_core_peleave(ReconnVM *vm) {
  reconn_vm_leave_namespace(vm);
  return 0;
}

// int reconn_mod_core_p(ReconnVM *vm) {
//  return 0;
//}

int reconn_mod_core_pnop(ReconnVM *vm) { return 0; }

int reconn_mod_core_pdo(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  char *name = reconn_buffer_pop_cstring(&vm->value_stack);
  reconn_vm_do_token(vm, name);
  free(name);
  return 0;
}

int reconn_mod_core_pwhen(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 1)) {
    vm->got_error = 1;
    return -1;
  }
  char *on_true = reconn_buffer_pop_cstring(&vm->value_stack);
  ReconnValueKind kind =
      reconn_buffer_kind_at(&vm->value_stack, vm->value_stack.lasti);
  int is_true =
      reconn_value_is_true(kind, reconn_buffer_pop_void(&vm->value_stack));

  if (is_true) {
    reconn_vm_push_run(vm, on_true);
  }

  free(on_true);
  return 0;
}

int reconn_mod_core_pif(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 2)) {
    vm->got_error = 1;
    return -1;
  }
  char *on_false = reconn_buffer_pop_cstring(&vm->value_stack);
  char *on_true = reconn_buffer_pop_cstring(&vm->value_stack);
  ReconnValueKind kind =
      reconn_buffer_kind_at(&vm->value_stack, vm->value_stack.lasti);
  int is_true =
      reconn_value_is_true(kind, reconn_buffer_pop_void(&vm->value_stack));

  if (is_true) {
    reconn_vm_push_run(vm, on_true);
  } else {
    reconn_vm_push_run(vm, on_false);
  }

  free(on_true);
  free(on_false);
  return 0;
}

int reconn_mod_core_include(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }

  char *filename = reconn_buffer_pop_cstring(&vm->value_stack);
  reconn_util_do_file(vm, filename);
  free(filename);

  return 0;
}

int reconn_mod_core_reset(ReconnVM *vm) {
  reconn_vm_reset_soft(vm);
  return 0;
}

int reconn_mod_core_register_all(ReconnVM *vm) {
  reconn_vm_add_primary(vm, "[", reconn_mod_core_pstart_wipe);
  reconn_vm_add_primary(vm, "[/", reconn_mod_core_pstart);
  reconn_vm_add_compile(vm, "]", reconn_mod_core_cstop);
  reconn_vm_add_primary(vm, "def", reconn_mod_core_pdef);
  reconn_vm_add_primary(vm, "include", reconn_mod_core_include);

  reconn_vm_add_primary(vm, "enter", reconn_mod_core_penter);
  reconn_vm_add_primary(vm, "leave", reconn_mod_core_peleave);

  reconn_vm_add_primary(vm, "nop", reconn_mod_core_pnop);
  reconn_vm_add_primary(vm, "do", reconn_mod_core_pdo);
  reconn_vm_add_primary(vm, "when", reconn_mod_core_pwhen);
  reconn_vm_add_primary(vm, "if", reconn_mod_core_pif);

  reconn_vm_add_primary(vm, "stack", reconn_mod_core_pstack);
  reconn_vm_add_primary(vm, "dstack", reconn_mod_core_pdstack);
  reconn_vm_add_primary(vm, "bye", reconn_mod_core_pstop);
  reconn_vm_add_primary(vm, "reset", reconn_mod_core_reset);
  return 0;
}

#endif