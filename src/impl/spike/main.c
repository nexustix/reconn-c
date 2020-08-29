//#include "reconn/data/bucket.h"
#include "reconn/data/buffer.h"
#include "reconn/data/buffer_float.h"
#include "reconn/data/buffer_int.h"
#include "reconn/data/buffer_string.h"
#include "reconn/data/number.h"
//#include "reconn/data/value.h"
#include "reconn/module/comparison.h"
#include "reconn/module/core.h"
#include "reconn/module/io.h"
#include "reconn/module/math.h"
#include "reconn/module/stack.h"
#include "reconn/parse.h"
#include "reconn/util.h"
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

  reconn_buffer_push_bytestring(
      &stack, "the quick brown fox jumps over the lazy dog", 43);
  reconn_buffer_push_cstring(&stack,
                             "the quick brown fox jumps over the lazy dog");

  // char *str = reconn_buffer_pop_cstring(&stack);
  // printf(">%s<", str);
  // free(str);
  free(reconn_buffer_pop_cstring(&stack));
  free(reconn_buffer_pop_bytestring(&stack));

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

void repl(ReconnVM *vm) {

  ReconnBuffer inputBuffer = reconn_makeBuffer();

  size_t size = 0;
  char *data = NULL;

  fprintf(stderr, "Reconn REPL\n");
  fprintf(stderr, "Version: INDEV\n");
  fprintf(stderr, ">");
  while (vm->running) {
    getline(&data, &size, stdin);
    reconn_parse_tokens(data, &inputBuffer);

    while (inputBuffer.count) {
      char *token = reconn_buffer_pop_cstring(&inputBuffer);
      reconn_buffer_push_cstring(&vm->run_stack, token);
      free(token);
    }

    while (reconn_vm_tick(vm))
      ;
    if (vm->got_error) {
      printf("<!> Resetting enviroment\n");
      // reconn_buffer_reset(&vm->run_stack);
      // reconn_buffer_reset(&vm->value_stack);
      reconn_vm_reset_soft(vm);
    }
    if (vm->running) {
      fprintf(stderr, ">");
    }
  }

  reconn_buffer_free(&inputBuffer, 0);
  free(data);
}

int say_hello(ReconnVM *vm) {
  printf("HELLO THERE\n");
  return 0;
}

int main() {
  tbd();

  // const char *cake = reconn_value_kind_to_string(RECONN_VALUE_S64);
  // printf("%s\n", cake);

  /*
  ReconnNumber num_a = reconn_makeNumber(12304510000, 6);
  ReconnNumber num_b = reconn_makeNumber(12351000000, 6);
  ReconnNumber num_c = reconn_number_from_double(1234234223.99);
  double d_c = reconn_number_to_double(&num_c);


  reconn_number_print(&num_a);
  reconn_number_print(&num_b);
  reconn_number_print(&num_c);
  printf("%lf\n", d_c);
  */

  ReconnVM vm = reconn_makeVM();
  reconn_vm_add_primary(&vm, "hello", say_hello);

  // reconn_vm_add_primary(&vm, "[", pcompile_start);
  // reconn_vm_add_compile(&vm, "]", ccompile_stop);
  // reconn_vm_add_primary(&vm, "def", pdef);

  reconn_mod_core_register_all(&vm);
  reconn_mod_io_register_all(&vm);
  reconn_mod_math_register_all(&vm);
  reconn_mod_comparison_register_all(&vm);
  reconn_mod_stack_register_all(&vm);

  // do_file();
  // reconn_util_do_file(&vm, "test.rcn");

  repl(&vm);
  reconn_vm_free(&vm, 0);
}