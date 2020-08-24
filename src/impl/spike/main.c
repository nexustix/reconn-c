//#include "reconn/data/bucket.h"
#include "reconn/data/buffer.h"
//#include "reconn/data/stack.h"
#include "reconn/data/value.h"
#include "reconn/vm.h"
#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

void tbd() {
  ReconnBuffer stack = reconn_makeBuffer();
  reconn_buffer_push_u8(&stack, UCHAR_MAX);
  reconn_buffer_push_u16(&stack, USHRT_MAX);
  reconn_buffer_push_u32(&stack, ULONG_MAX);
  reconn_buffer_push_u64(&stack, ULLONG_MAX);

  reconn_buffer_push_s8(&stack, CHAR_MIN);
  reconn_buffer_push_s16(&stack, SHRT_MIN);
  reconn_buffer_push_s32(&stack, LONG_MIN);
  reconn_buffer_push_s64(&stack, LLONG_MIN);

  reconn_buffer_push_f32(&stack, 0x0451);
  reconn_buffer_push_f64(&stack, 0x0451);

  reconn_buffer_push_string(&stack,
                            "the quick brown fox jumps over the lazy dog", 43);
  reconn_buffer_push_cstring(&stack,
                             "the quick brown fox jumps over the lazy dog");

  free(reconn_buffer_pop_cstring(&stack));
  free(reconn_buffer_pop_string(&stack));

  // reconn_stack_print(&stack);

  assert(reconn_buffer_pop_f64(&stack) == 0x0451);
  assert(reconn_buffer_pop_f32(&stack) == 0x0451);

  assert(reconn_buffer_pop_s64(&stack) == LLONG_MIN);
  assert(reconn_buffer_pop_s32(&stack) == LONG_MIN);
  assert(reconn_buffer_pop_s16(&stack) == SHRT_MIN);
  assert(reconn_buffer_pop_s8(&stack) == CHAR_MIN);

  assert(reconn_buffer_pop_u64(&stack) == ULLONG_MAX);
  assert(reconn_buffer_pop_u32(&stack) == ULONG_MAX);
  assert(reconn_buffer_pop_u16(&stack) == USHRT_MAX);
  assert(reconn_buffer_pop_u8(&stack) == UCHAR_MAX);

  reconn_buffer_free(&stack, 0);
}

int say_hello(ReconnVM *vm) {
  printf("HELLO THERE\n");
  return 0;
}

int main() {
  tbd();

  ReconnVM vm = reconn_makeVM();

  reconn_vm_add_primary(&vm, "hello", say_hello);
  reconn_vm_enter_namespace(&vm, "apha");
  // reconn_vm_add_primary(&vm, "hello", say_hello);
  reconn_vm_compile_append(&vm, "hello");
  reconn_vm_compile_append(&vm, "hello");
  reconn_vm_compile_append(&vm, "hello");
  reconn_vm_add_secondary(&vm, "cheese");
  reconn_vm_add_secondary(&vm, "foo");
  reconn_vm_add_secondary(&vm, "bar");
  reconn_vm_enter_namespace(&vm, "beta");
  // reconn_vm_do_token(&vm, "hello");
  reconn_vm_do_token(&vm, "cheese");

  while (reconn_vm_tick(&vm))
    ;

  reconn_vm_free(&vm, 0);

  /*
  ReconnVM vm = reconn_makeVM();

  reconn_vm_enter_namespace(&vm, "alpha");
  reconn_vm_enter_namespace(&vm, "beta");
  reconn_vm_enter_namespace(&vm, "gamma");
  reconn_vm_enter_namespace(&vm, "delta");
  reconn_vm_enter_namespace(&vm, "epsilon");
  char *cake = reconn_vm_namespace_token(&vm, "bake", 5);
  // char *cake = reconn_vm_namespace_fragment(&vm, 1);
  printf(">%s<\n", cake);
  printf(">%lu<\n", reconn_vm_namespace_depth(&vm));

  reconn_vm_namespace_fragment(&vm, 1);
  */

  /*
  ReconnBucket bucket = reconn_makeBucket();

  int bestval = 451;

  reconn_bucket_add(&bucket, &bestval, "toast");

  int *fuu = reconn_bucket_get(&bucket, "toast");

  printf(">%i<\n", *fuu);
  */
}