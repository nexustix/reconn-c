#include <stdio.h>
#include <unistd.h>

#include "bignum.h"
#include "dictionary.h"
#include "element.h"
#include "list.h"
#include "parse.h"
#include "util.h"
#include "vm.h"
#include "vocabularies/math/arithmetic.h"

// HACK
static char *content_root;
// char *get_content_root() { return content_root; }

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

// TODO implement
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

// HACK
void _include(VM *self) {
  static Element *e;
  if (!e) e = newElement();

  vm_pop_value(self, e);
  assert(e->kind == ELEMENT_BIGNUM);
  const char *sub_path = bignum_to_cstring(element_get_bignum(e));

  size_t content_root_length = strlen(content_root);
  size_t sub_path_length = strlen(content_root);

  char *complete_path =
      calloc(content_root_length + sub_path_length + strlen(".rcn") + 1, 1);

  strcat(complete_path, content_root);
  strcat(complete_path, "/");
  strcat(complete_path, sub_path);
  strcat(complete_path, ".rcn");

  List *tokens = newList(16);
  FILE *handle = NULL;
  size_t size;
  char *data = malloc(1024);
  size_t tbd;

  // printf(">%s<\n", complete_path);
  handle = fopen(complete_path, "r");

  if (handle) {
    int firstline = 1;
    while ((tbd = getline(&data, &size, handle)) != -1) {
      // printf(">%s<\n", data);
      if (firstline) {
        firstline = 0;
        // shebang support
        if (strncmp(data, "#!", strlen("#!")) == 0) {
          // if (strncmp(data, "#", strlen("#")) == 0) {
          continue;
        }
      }
      parse_tokens(data, tokens);
      vm_execute_all(self, tokens, 0);
      tokens->top = 0;
    }
    fclose(handle);
  }
}

void register_words(VM *vm) {
  vm_add_primary(vm, "def", _def);
  vm_add_compile(vm, "def", _def_compile);
  vm_add_compile(vm, "end", _end_compile);

  vm_add_primary(vm, "println", _println);
  vm_add_primary(vm, "s", _print_value_stack);

  vm_add_primary(vm, "add", voc_mat_ari_add);
  vm_add_primary(vm, "sub", voc_mat_ari_sub);
  vm_add_primary(vm, "+", voc_mat_ari_add);
  vm_add_primary(vm, "-", voc_mat_ari_sub);

  vm_add_primary(vm, "namespace", _print_namespace);
  vm_add_primary(vm, "#enter", _enter);
  vm_add_primary(vm, "#leave", _leave);

  vm_add_primary(vm, "#include", _include);

  vm_add_primary(vm, "spam", _spam);
  vm_add_primary(vm, "cake.spam", _spam);
  vm_add_primary(vm, "wonderful", _wonderful);
}

int main(int argc, const char *argv[]) {
  List *tokens = newList(16);
  size_t size;
  char *data = malloc(1024);
  size_t tbd;

  // char *content_root = getenv("RCNPATH");
  content_root = getenv("RCNPATH");

  if (!content_root) {
    // FIXME questionable constant
    content_root = malloc(4096);
    getcwd(content_root, 4096);
  }

  VM *vm = newVM();
  register_words(vm);

  FILE *handle = NULL;

  printf("argc >%s<\n", content_root);

  if (argc > 1) {
    handle = fopen(argv[1], "r");
  }
  if (handle) {
    int firstline = 1;
    while ((tbd = getline(&data, &size, handle)) != -1) {
      if (firstline) {
        firstline = 0;
        // shebang support
        if (strncmp(data, "#!", strlen("#!")) == 0) {
          // if (strncmp(data, "#", strlen("#")) == 0) {
          continue;
        }
      }
      parse_tokens(data, tokens);
      vm_execute_all(vm, tokens, 0);
      tokens->top = 0;
    }
    fclose(handle);
  } else {
    printf("Reconn REPL\n");
    printf("Version: INDEV\n");
    while (1) {
      getline(&data, &size, stdin);
      parse_tokens(data, tokens);
      vm_execute_all(vm, tokens, 1);
      tokens->top = 0;
    }
  }

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }
