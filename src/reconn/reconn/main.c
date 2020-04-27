
#include <assert.h>
//#include <reconnapi.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "reconn/data/dictionary.h"
#include "reconn/data/element.h"
#include "reconn/data/list.h"
#include "reconn/parse.h"
//#include "test.h"
#include "modules/core/core.h"
#include "reconn/util.h"
#include "reconn/vm.h"

/*
// HACK
static char *content_root;

int _def(ReconnVM *self) {
  rcn_vm_push_state(self, RECONN_STATE_COMPILE);
  return 0;
}

int _def_compile(ReconnVM *self) {
  rcn_vm_push_state(self, RECONN_STATE_HARD);
  rcn_vm_push_wordbuffer(self, TOKEN_DEF);
  return 0;
}

int _end_compile(ReconnVM *self) {
  static ReconnElement *e;
  if (!e) e = rcn_newReconnElement();

  ReconnList *new_word = rcn_newReconnList(2);
  for (unsigned long i = 2; i <= self->word_buffer->top; i++) {
    e = rcn_list_get_at(self->word_buffer, i);
    assert(e->kind == RECONN_ELEMENT_CSTRING);
    rcn_list_push(new_word, e);
  }
  e = rcn_list_get_at(self->word_buffer, 1);
  // printf("new word called >%s<\n", element_get_cstring(e));
  rcn_vm_add_secondary(self, rcn_element_get_cstring(e), new_word);
  rcn_vm_pop_state(self);
  self->word_buffer->top = 0;
  return 0;
}

// TODO implement
// void _do(ReconnVM *self) {}

// FIXME values are no longer just bignums

int _print_value_stack(ReconnVM *self) {
  static ReconnElement *e;
  if (!e) e = rcn_newReconnElement();
  // ReconnElement *e;
  unsigned long index = 0;
  // printf(" | ");
  printf(" ");
  for (unsigned long i = 0; i < self->value_stack->top; i++) {
    index = self->value_stack->top - i;
    // printf("[%s] ", bignum_to_cstring(
    //                    element_get_bignum(list_get_at(self->value_stack,
    //                    i))));
    e = rcn_list_get_at(self->value_stack, index);
    // printf("(%d)[%s] ", e->kind, element_to_cstring(e));
    printf("(%s)[%s] ", rcn_element_kind_to_cstring(e),
           rcn_element_data_to_cstring(e));
  }
  // printf("|>");
  printf("\n");
  return 0;
}

int _print_namespace(ReconnVM *self) {
  printf(">%s<\n", rcn_vm_namespace(self));
  return 0;
}

int _enter(ReconnVM *self) {
  static ReconnElement *e;
  if (!e) e = rcn_newReconnElement();
  rcn_vm_pop_value(self, e);
  // assert(e->kind == RECONN_ELEMENT_BIGNUM);
  // vm_push_namespace(self, bignum_to_cstring(element_get_bignum(e)));
  assert(e->kind == RECONN_ELEMENT_CSTRING);
  rcn_vm_push_namespace(self, rcn_element_get_cstring(e));
  return 0;
}

int _leave(ReconnVM *self) {
  rcn_vm_pop_namespace(self);
  return 0;
}

// HACK
int _include(ReconnVM *self) {
  static ReconnElement *e;
  if (!e) e = rcn_newReconnElement();

  rcn_vm_pop_value(self, e);
  // assert(e->kind == RECONN_ELEMENT_BIGNUM);
  // const char *sub_path = bignum_to_cstring(element_get_bignum(e));
  assert(e->kind == RECONN_ELEMENT_CSTRING);
  const char *sub_path = rcn_element_get_cstring(e);

  size_t content_root_length = strlen(content_root);
  size_t sub_path_length = strlen(content_root);

  char *complete_path =
      calloc(content_root_length + sub_path_length + strlen(".rcn") + 1, 1);

  strcat(complete_path, content_root);
  strcat(complete_path, "/");
  strcat(complete_path, sub_path);
  strcat(complete_path, ".rcn");

  ReconnList *tokens = rcn_newReconnList(16);
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
      rcn_parse_tokens(data, tokens);
      rcn_vm_execute_all(self, tokens, 0);
      tokens->top = 0;
    }
    fclose(handle);
  }
  return 0;
}

int _use(ReconnVM *self) {
  static ReconnElement *e;
  if (!e) e = rcn_newReconnElement();

  rcn_vm_pop_value(self, e);
  // assert(e->kind == RECONN_ELEMENT_BIGNUM);
  // const char *use_name = bignum_to_cstring(element_get_bignum(e));
  assert(e->kind == RECONN_ELEMENT_CSTRING);
  const char *use_name = rcn_element_get_cstring(e);

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
*/

int _println(ReconnVM *self) {
  static ReconnElement *e;
  if (!e) e = rcn_newReconnElement();
  rcn_vm_pop_value(self, e);
  // assert(e->kind == RECONN_ELEMENT_CSTRING);
  // printf("%s\n", rcn_element_get_cstring(e));
  printf("%s\n", rcn_element_data_to_cstring(e));
  free(e);
  return 0;
}

void register_words(ReconnVM *vm) {
  // rcn_vm_add_primary(vm, "def", _def);
  // rcn_vm_add_compile(vm, "def", _def_compile);
  // rcn_vm_add_compile(vm, "end", _end_compile);

  rcn_vm_add_primary(vm, "println", _println);
  // rcn_vm_add_primary(vm, "s", _print_value_stack);

  // rcn_vm_add_primary(vm, "#namespace", _print_namespace);
  // rcn_vm_add_primary(vm, "#enter", _enter);
  // rcn_vm_add_primary(vm, "#leave", _leave);

  // rcn_vm_add_primary(vm, "#include", _include);
  // rcn_vm_add_primary(vm, "#use", _use);
}

int main(int argc, const char *argv[]) {
  ReconnList *tokens = rcn_newReconnList(16);
  size_t size;
  char *data = malloc(1024);
  size_t tbd;

  // bake_cake("strawberry");

  // char *content_root = getenv("RCNPATH");
  core_content_root = getenv("RCNPATH");

  if (!core_content_root) {
    // FIXME questionable constant
    core_content_root = malloc(4096);
    getcwd(core_content_root, 4096);
  }

  ReconnVM *vm = rcn_newReconnVM();
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
      rcn_parse_tokens(data, tokens);
      rcn_vm_execute_all(vm, tokens, 0);
      tokens->top = 0;
    }
    fclose(handle);
  } else {
    fprintf(stderr, "Reconn REPL\n");
    fprintf(stderr, "Version: INDEV\n");
    fprintf(stderr, "RCNPATH: >%s<\n", core_content_root);
    while (1) {
      getline(&data, &size, stdin);
      rcn_parse_tokens(data, tokens);
      rcn_vm_execute_all(vm, tokens, 1);
      tokens->top = 0;
    }
  }

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }