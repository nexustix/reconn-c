#include <stdio.h>

#include "bignum.h"
#include "dictionary.h"
#include "element.h"
#include "list.h"
#include "vm.h"

void _spam(VM* self) { printf("Spam\n"); }
void _wonderful(VM* self) { printf("Wonderful Spam\n"); }

int main(int argc, const char* argv[]) {
  Element *e = newElement();

  VM *pip = newVM();

  List *wiking = newList(16);
  list_push(wiking, element_set_cstring(e, "spam"));
  list_push(wiking, element_set_cstring(e, "spam"));
  list_push(wiking, element_set_cstring(e, "spam"));
  list_push(wiking, element_set_cstring(e, "wonderful"));
  list_push(wiking, element_set_cstring(e, "spam"));
  list_push(wiking, element_set_cstring(e, "wonderful"));
  list_push(wiking, element_set_cstring(e, "wonderful"));
  
  vm_add_primary(pip, "spam", _spam);
  vm_add_primary(pip, "wonderful", _wonderful);
  vm_add_secondary(pip, "wiking", wiking);

  vm_do(pip, "wiking");

  vm_run(pip);

  // printf("Aloha, edit \"src/main.c\" to get started\n");

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char* argv[]) { return main(argc, argv); }