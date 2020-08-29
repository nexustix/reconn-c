#ifndef RECONN_UTIL_H
#define RECONN_UTIL_H

#include "parse.h"
#include "vm.h"

int reconn_util_do_file(ReconnVM *vm, char *path) {
  FILE *handle = NULL;
  size_t tbd;
  size_t size;
  // char *data = malloc(1024);
  char *data = NULL;
  ReconnBuffer inputBuffer = reconn_makeBuffer();
  handle = fopen(path, "r");

  if (handle) {
    int firstline = 1;
    while ((tbd = getline(&data, &size, handle)) != -1) {
      if (firstline) {
        firstline = 0;
        // shebang support
        if (strncmp(data, "#!", strlen("#!")) == 0) {
          continue;
        }
      }
      reconn_parse_tokens(data, &inputBuffer);
      while (inputBuffer.count) {
        char *token = reconn_buffer_pop_cstring(&inputBuffer);
        reconn_buffer_push_cstring(&vm->run_stack, token);
        free(token);
      }

      while (reconn_vm_tick(vm))
        ;
    }
    fclose(handle);
    reconn_buffer_free(&inputBuffer, 0);
    free(data);
    return 1;
  }
  reconn_buffer_free(&inputBuffer, 0);
  free(data);
  return 0;
}

#endif