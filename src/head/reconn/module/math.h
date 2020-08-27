#ifndef RECONN_MODULES_MATH_H
#define RECONN_MODULES_MATH_H

#include "../data/buffer.h"
#include "../data/value.h"
#include "../vm.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

int reconn_mod_math_add(ReconnVM *vm) {
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
    reconn_buffer_push_f64(&vm->value_stack, a + b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s64(&vm->value_stack, a + b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_u64(&vm->value_stack, a + b);
  }
  return 0;
}

int reconn_mod_math_sub(ReconnVM *vm) {
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
    reconn_buffer_push_f64(&vm->value_stack, a - b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s64(&vm->value_stack, a - b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_u64(&vm->value_stack, a - b);
  }
  return 0;
}

int reconn_mod_math_mul(ReconnVM *vm) {
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
    reconn_buffer_push_f64(&vm->value_stack, a * b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s64(&vm->value_stack, a * b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_u64(&vm->value_stack, a * b);
  }
  return 0;
}

int reconn_mod_math_rdiv(ReconnVM *vm) {
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
    // double b = reconn_value_to_f64(kind_b, value_b);
    // double a = reconn_value_to_f64(kind_a, value_a);
    // reconn_buffer_push_f64(&vm->value_stack, floor((a / b) + 0.5));
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s64(&vm->value_stack, a / b);
    reconn_buffer_push_s64(&vm->value_stack, a % b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s64(&vm->value_stack, a / b);
    reconn_buffer_push_s64(&vm->value_stack, a % b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_u64(&vm->value_stack, a / b);
    reconn_buffer_push_u64(&vm->value_stack, a % b);
  }
  return 0;
}

int reconn_mod_math_fdiv(ReconnVM *vm) {
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

  double b = reconn_value_to_f64(kind_b, value_b);
  double a = reconn_value_to_f64(kind_a, value_a);
  reconn_buffer_push_f64(&vm->value_stack, a / b);

  return 0;
  return 0;
}

int reconn_mod_math_idiv(ReconnVM *vm) {
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
    // double b = reconn_value_to_f64(kind_b, value_b);
    // double a = reconn_value_to_f64(kind_a, value_a);
    // reconn_buffer_push_f64(&vm->value_stack, floor((a / b) + 0.5));
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s64(&vm->value_stack, a / b);
    // reconn_buffer_push_s64(&vm->value_stack, a % b);
  } else if (reconn_value_is_signed(kind_a) || reconn_value_is_signed(kind_b)) {
    long long b = reconn_value_to_s64(kind_b, value_b);
    long long a = reconn_value_to_s64(kind_a, value_a);
    reconn_buffer_push_s64(&vm->value_stack, a / b);
    // reconn_buffer_push_s64(&vm->value_stack, a % b);
  } else {
    long long b = reconn_value_to_u64(kind_b, value_b);
    long long a = reconn_value_to_u64(kind_a, value_a);
    reconn_buffer_push_u64(&vm->value_stack, a / b);
    // reconn_buffer_push_u64(&vm->value_stack, a % b);
  }
  return 0;
}

// int reconn_mod_math_mod(ReconnVM *vm) { return 0; }

// int reconn_mod_math_(ReconnVM *vm) {
//  return 0;
//}

int reconn_mod_math_register_all(ReconnVM *vm) {
  reconn_vm_add_primary(vm, "+", reconn_mod_math_add);
  reconn_vm_add_primary(vm, "-", reconn_mod_math_sub);
  reconn_vm_add_primary(vm, "*", reconn_mod_math_mul);
  reconn_vm_add_primary(vm, "/%", reconn_mod_math_rdiv);
  reconn_vm_add_primary(vm, "//", reconn_mod_math_idiv);
  reconn_vm_add_primary(vm, "/", reconn_mod_math_fdiv);
  return 0;
}

#endif