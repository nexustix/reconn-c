#ifndef RECONN_MODULES_COMPARISON_H
#define RECONN_MODULES_COMPARISON_H

#include "../vm.h"

int reconn_mod_comp_gt(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind_b = reconn_buffer_kind_at(&vm->value_stack, -1);
  const ReconnValueKind kind_a = reconn_buffer_kind_at(&vm->value_stack, -2);

  const void *value_b = reconn_buffer_pop_void(&vm->value_stack);
  const void *value_a = reconn_buffer_pop_void(&vm->value_stack);

  if (!(reconn_value_is_number(kind_a) && reconn_value_is_number(kind_b))) {
    vm->got_error = 1;
    return -1;
  }

  if (reconn_value_is_float(kind_a) || reconn_value_is_float(kind_b)) {
    double b = reconn_value_to_f64(kind_b, value_b);
    double a = reconn_value_to_f64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a > b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a > b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a > b);
  }
  return 0;
}
int reconn_mod_comp_lt(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind_b = reconn_buffer_kind_at(&vm->value_stack, -1);
  const ReconnValueKind kind_a = reconn_buffer_kind_at(&vm->value_stack, -2);

  const void *value_b = reconn_buffer_pop_void(&vm->value_stack);
  const void *value_a = reconn_buffer_pop_void(&vm->value_stack);

  if (!(reconn_value_is_number(kind_a) && reconn_value_is_number(kind_b))) {
    vm->got_error = 1;
    return -1;
  }

  if (reconn_value_is_float(kind_a) || reconn_value_is_float(kind_b)) {
    double b = reconn_value_to_f64(kind_b, value_b);
    double a = reconn_value_to_f64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a < b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a < b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a < b);
  }
  return 0;
}

int reconn_mod_comp_eq(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind_b = reconn_buffer_kind_at(&vm->value_stack, -1);
  const ReconnValueKind kind_a = reconn_buffer_kind_at(&vm->value_stack, -2);

  const void *value_b = reconn_buffer_pop_void(&vm->value_stack);
  const void *value_a = reconn_buffer_pop_void(&vm->value_stack);

  if (!(reconn_value_is_number(kind_a) && reconn_value_is_number(kind_b))) {
    vm->got_error = 1;
    return -1;
  }

  if (reconn_value_is_float(kind_a) || reconn_value_is_float(kind_b)) {
    double b = reconn_value_to_f64(kind_b, value_b);
    double a = reconn_value_to_f64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a == b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a == b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a == b);
  }
  return 0;
}

int reconn_mod_comp_ge(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind_b = reconn_buffer_kind_at(&vm->value_stack, -1);
  const ReconnValueKind kind_a = reconn_buffer_kind_at(&vm->value_stack, -2);

  const void *value_b = reconn_buffer_pop_void(&vm->value_stack);
  const void *value_a = reconn_buffer_pop_void(&vm->value_stack);

  if (!(reconn_value_is_number(kind_a) && reconn_value_is_number(kind_b))) {
    vm->got_error = 1;
    return -1;
  }

  if (reconn_value_is_float(kind_a) || reconn_value_is_float(kind_b)) {
    double b = reconn_value_to_f64(kind_b, value_b);
    double a = reconn_value_to_f64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a >= b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a >= b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a >= b);
  }
  return 0;
}

int reconn_mod_comp_le(ReconnVM *vm) {
  if (!(reconn_buffer_count(&vm->value_stack) > 0)) {
    vm->got_error = 1;
    return -1;
  }
  const ReconnValueKind kind_b = reconn_buffer_kind_at(&vm->value_stack, -1);
  const ReconnValueKind kind_a = reconn_buffer_kind_at(&vm->value_stack, -2);

  const void *value_b = reconn_buffer_pop_void(&vm->value_stack);
  const void *value_a = reconn_buffer_pop_void(&vm->value_stack);

  if (!(reconn_value_is_number(kind_a) && reconn_value_is_number(kind_b))) {
    vm->got_error = 1;
    return -1;
  }

  if (reconn_value_is_float(kind_a) || reconn_value_is_float(kind_b)) {
    double b = reconn_value_to_f64(kind_b, value_b);
    double a = reconn_value_to_f64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a <= b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a <= b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_s8(&vm->value_stack, a <= b);
  }
  return 0;
}
// int reconn_mod_comp_(ReconnVM *vm) { return 0; }

int reconn_mod_comparison_register_all(ReconnVM *vm) {
  reconn_vm_add_primary(vm, ">", reconn_mod_comp_gt);
  reconn_vm_add_primary(vm, "<", reconn_mod_comp_lt);
  reconn_vm_add_primary(vm, "=", reconn_mod_comp_eq);
  reconn_vm_add_primary(vm, ">=", reconn_mod_comp_ge);
  reconn_vm_add_primary(vm, "<=", reconn_mod_comp_le);
  return 0;
}

#endif