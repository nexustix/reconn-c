#include <stdio.h>

#include "bignum.h"
#include "dictionary.h"
#include "element.h"
#include "list.h"
#include "vm.h"
#include "util.h"

#include "parse.h"

void _spam(VM* self) { printf("Spam\n"); }
void _wonderful(VM* self) { printf("Wonderful Spam\n"); }

void _def(VM *self){
  vm_state_push(self, STATE_COMPILE);
}

void _def_compile(VM *self){
  vm_wordbuffer_push(self, TOKEN_DEF);
  vm_state_push(self, STATE_HARD);
}

void _end_compile(VM *self){
  static Element* e;
  if (!e) e = newElement();
  
  List *new_word = newList(2);
  for (unsigned long i=2; i<= self->word_buffer->top; i++){
    e = list_get_at(self->word_buffer, i);
    assert(e->kind == ELEMENT_CSTRING);
    list_push(new_word, e);
  }
  e = list_get_at(self->word_buffer, 1);
  vm_add_secondary(self, element_get_cstring(e), new_word);
  vm_state_pop(self);
}

void _do(VM *self){}

int main(int argc, const char* argv[]) {
  //Element *e = newElement();
  
  VM *pip = newVM();

  vm_add_primary(pip, "spam", _spam);
  vm_add_primary(pip, "wonderful", _wonderful);

  vm_add_primary(pip, "def", _def);
  vm_add_compile(pip, "def", _def_compile);
  vm_add_compile(pip, "end", _end_compile);

  List *tokens = newList(16);

  size_t size;
  char *data = NULL;

  while (1){
    //printf("\n>");
    getline(&data, &size, stdin);
    parse_tokens(data, tokens);

    vm_execute_all(pip, tokens, 0);
    tokens->top = 0;
  }

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char* argv[]) { return main(argc, argv); }


