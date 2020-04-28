
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
int _println(ReconnVM *self) {
  static ReconnElement *e;
  if (!e) e = rcn_newReconnElement();
  rcn_vm_pop_value(self, e);
  printf("%s\n", rcn_element_data_to_cstring(e));
  free(e);
  return 0;
}
*/

void register_words(ReconnVM *vm) {
  // rcn_vm_add_primary(vm, "println", _println);
  core_register_all(vm);
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
    fprintf(stderr, ">");
    while (1) {
      getline(&data, &size, stdin);
      rcn_parse_tokens(data, tokens);
      rcn_vm_execute_all(vm, tokens, 1);
      tokens->top = 0;
      fprintf(stderr, ">");
    }
  }

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }