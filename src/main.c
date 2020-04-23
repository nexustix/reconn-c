#include <stdio.h>

#include "bignum.h"
#include "dictionary.h"
#include "element.h"
#include "list.h"
#include "parse.h"
#include "util.h"
#include "vm.h"
#include "vocabularies/math/arithmetic.h"

void _spam(VM *self) { printf("Spam\n"); }
void _wonderful(VM *self) { printf("Wonderful Spam\n"); }

void _def(VM *self) { vm_push_state(self, STATE_COMPILE); }

void _def_compile(VM *self) {
  vm_push_state(self, STATE_HARD);
  vm_push_wordbuffer(self, TOKEN_DEF);
}

void _end_compile(VM *self) {
  static Element *e;
  if (!e) e = newElement();

  List *new_word = newList(2);
  for (unsigned long i = 2; i <= self->word_buffer->top; i++) {
    e = list_get_at(self->word_buffer, i);
    assert(e->kind == ELEMENT_CSTRING);
    list_push(new_word, e);
  }
  e = list_get_at(self->word_buffer, 1);
  // printf("new word called >%s<\n", element_get_cstring(e));
  vm_add_secondary(self, element_get_cstring(e), new_word);
  vm_pop_state(self);
  self->word_buffer->top = 0;
}

void _do(VM *self) {}

void _println(VM *self) {
  static Element *e;
  if (!e) e = newElement();
  vm_pop_value(self, e);
  assert(e->kind == ELEMENT_BIGNUM);
  printf("%s\n", bignum_to_cstring(element_get_bignum(e)));
  free(e);
}

void _print_value_stack(VM *self) {
  printf(" | ");
  for (unsigned long i = 1; i <= self->value_stack->top; i++) {
    printf("[%s] ", bignum_to_cstring(
                        element_get_bignum(list_get_at(self->value_stack, i))));
  }
  printf("|>\n");
}

void _print_namespace(VM *self) { printf(">%s<\n", vm_namespace(self)); }

void _enter(VM *self) {
  static Element *e;
  if (!e) e = newElement();
  vm_pop_value(self, e);
  assert(e->kind == ELEMENT_BIGNUM);
  // printf("entering >%s<\n", bignum_to_cstring(element_get_bignum(e)));
  vm_push_namespace(self, bignum_to_cstring(element_get_bignum(e)));
}

void _leave(VM *self) { vm_pop_namespace(self); }

int main(int argc, const char *argv[]) {
  VM *pip = newVM();

  vm_add_primary(pip, "def", _def);
  vm_add_compile(pip, "def", _def_compile);
  vm_add_compile(pip, "end", _end_compile);

  vm_add_primary(pip, "println", _println);
  vm_add_primary(pip, "s", _print_value_stack);

  vm_add_primary(pip, "add", voc_mat_ari_add);
  vm_add_primary(pip, "sub", voc_mat_ari_sub);
  vm_add_primary(pip, "+", voc_mat_ari_add);
  vm_add_primary(pip, "-", voc_mat_ari_sub);

  vm_add_primary(pip, "namespace", _print_namespace);
  vm_add_primary(pip, "#enter", _enter);
  vm_add_primary(pip, "#leave", _leave);

  vm_add_primary(pip, "spam", _spam);
  vm_add_primary(pip, "cake.spam", _spam);
  vm_add_primary(pip, "wonderful", _wonderful);

  List *tokens = newList(16);

  size_t size;
  char *data = malloc(1024);

  printf("Reconn REPL\n");
  printf("Version: INDEV\n");
  while (1) {
    // printf("\n>");
    getline(&data, &size, stdin);
    parse_tokens(data, tokens);
    // for (unsigned long i=1; i<= tokens->top; i++){
    // printf(" >%s< ", element_get_cstring(list_get_at(tokens, i)));
    //}
    // printf("\n");
    vm_execute_all(pip, tokens, 1);
    tokens->top = 0;
  }

  /*
  vm_push_namespace(pip, "cake.toast");
  Element *e = vm_find_word(pip, "bake");
  if (e) {
    printf("something >%s<\n", e->id);
  } else {
    printf("nothing\n");
  }
  */

  // vm_push_namespace(pip, "cake.toast");
  // printf("%s\n", vm_spacename(pip, "cheese"));

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }
