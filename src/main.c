#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "dictionary.h"
#include "element.h"
#include "list.h"
#include "parse.h"
#include "util.h"
#include "vm.h"

// HACK
static char *content_root;

int _def(VM *self) {
  vm_push_state(self, STATE_COMPILE);
  return 0;
}

int _def_compile(VM *self) {
  vm_push_state(self, STATE_HARD);
  vm_push_wordbuffer(self, TOKEN_DEF);
  return 0;
}

int _end_compile(VM *self) {
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
  return 0;
}

// TODO implement
// void _do(VM *self) {}

int _println(VM *self) {
  static Element *e;
  if (!e) e = newElement();
  vm_pop_value(self, e);
  // assert(e->kind == ELEMENT_BIGNUM);
  // printf("%s\n", bignum_to_cstring(element_get_bignum(e)));
  assert(e->kind == ELEMENT_CSTRING);
  printf("%s\n", element_get_cstring(e));
  // FIXME investigate if contained string get's freed
  free(e);
  return 0;
}

// FIXME values are no longer just bignums

int _print_value_stack(VM *self) {
  static Element *e;
  if (!e) e = newElement();
  // Element *e;
  unsigned long index = 0;
  // printf(" | ");
  printf(" ");
  for (unsigned long i = 0; i < self->value_stack->top; i++) {
    index = self->value_stack->top - i;
    // printf("[%s] ", bignum_to_cstring(
    //                    element_get_bignum(list_get_at(self->value_stack,
    //                    i))));
    e = list_get_at(self->value_stack, index);
    // printf("(%d)[%s] ", e->kind, element_to_cstring(e));
    printf("(%s)[%s] ", element_kind_to_cstring(e), element_data_to_cstring(e));
  }
  // printf("|>");
  printf("\n");
  return 0;
}

int _print_namespace(VM *self) {
  printf(">%s<\n", vm_namespace(self));
  return 0;
}

int _enter(VM *self) {
  static Element *e;
  if (!e) e = newElement();
  vm_pop_value(self, e);
  // assert(e->kind == ELEMENT_BIGNUM);
  // vm_push_namespace(self, bignum_to_cstring(element_get_bignum(e)));
  assert(e->kind == ELEMENT_CSTRING);
  vm_push_namespace(self, element_get_cstring(e));
  return 0;
}

int _leave(VM *self) {
  vm_pop_namespace(self);
  return 0;
}

// HACK
int _include(VM *self) {
  static Element *e;
  if (!e) e = newElement();

  vm_pop_value(self, e);
  // assert(e->kind == ELEMENT_BIGNUM);
  // const char *sub_path = bignum_to_cstring(element_get_bignum(e));
  assert(e->kind == ELEMENT_CSTRING);
  const char *sub_path = element_get_cstring(e);

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
  return 0;
}

int _use(VM *self) {
  static Element *e;
  if (!e) e = newElement();

  vm_pop_value(self, e);
  // assert(e->kind == ELEMENT_BIGNUM);
  // const char *use_name = bignum_to_cstring(element_get_bignum(e));
  assert(e->kind == ELEMENT_CSTRING);
  const char *use_name = element_get_cstring(e);

  // if (use_name == "io") {
  if (0) {
  } else if (strcmp(use_name, "io") == 0) {
  } else if (strcmp(use_name, "string") == 0) {
  } else if (strcmp(use_name, "memory") == 0) {
  } else if (strcmp(use_name, "stack") == 0) {
  } else if (strcmp(use_name, "logic") == 0) {
  } else if (strcmp(use_name, "flow") == 0) {
  } else if (strcmp(use_name, "arithmetic") == 0) {
    // voc_mat_register_words(self);
  } else if (strcmp(use_name, "file") == 0) {
    // } else if (strcmp(use_name, "") == 0) {

  } else {
    fprintf(stderr, "<!> unable to find core module >%s<\n", use_name);
    exit(1);
  }
  return 0;
}

void register_words(VM *vm) {
  vm_add_primary(vm, "def", _def);
  vm_add_compile(vm, "def", _def_compile);
  vm_add_compile(vm, "end", _end_compile);

  vm_add_primary(vm, "println", _println);
  vm_add_primary(vm, "s", _print_value_stack);

  vm_add_primary(vm, "namespace", _print_namespace);
  vm_add_primary(vm, "#enter", _enter);
  vm_add_primary(vm, "#leave", _leave);

  vm_add_primary(vm, "#include", _include);
  vm_add_primary(vm, "#use", _use);
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
    fprintf(stderr, "Reconn REPL\n");
    fprintf(stderr, "Version: INDEV\n");
    fprintf(stderr, "RCNPATH: >%s<\n", content_root);
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