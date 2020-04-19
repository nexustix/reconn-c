#include <stdio.h>

#include "bignum.h"
#include "dictionary.h"
#include "element.h"
#include "list.h"
#include <stdio.h>

int main(int argc, const char *argv[]) {

  /*
  unsigned char number1[5] = {1, 2, 3, 4, 5};
  Bignum *uno = bignum_from_chars(10, sizeof(number1), number1);
  uno->negative = 0;

  unsigned char number2[3] = {4, 5, 1};
  Bignum *due = bignum_from_chars(10, sizeof(number2), number2);
  due->negative = 0;
  */

  /*
  List *list = newList(1);
  Element *ele = newElement();
  list_push(list, element_from_bignum(ele, bignum_from_chars(10,
  sizeof(number2), number2))); list_push(list, element_from_bignum(ele,
  bignum_from_chars(10, sizeof(number1), number1))); free(ele);

  Element *ele2 = newElement();

  list_pop(list, ele2);
  printf(">%s<\n", bignum_to_string(ele2->data));
  list_pop(list, ele2);
  printf(">%s<\n", bignum_to_string(ele2->data));
  */

  unsigned char number1[5] = {1, 2, 3, 4, 5};
  unsigned char number2[3] = {4, 5, 1};

  Dictionary *dict = newDictionary(4);

  Element *ele = newElement();

  dictionary_add(dict, "bob",
                 element_from_bignum(
                     ele, bignum_from_chars(10, sizeof(number1), number1)));
  dictionary_add(dict, "bob",
                element_from_bignum(
                    ele, bignum_from_chars(10, sizeof(number2), number2)));
  dictionary_add(dict, "bob",
                element_from_bignum(
                    ele, bignum_from_chars(10, sizeof(number1), number1)));
  free(ele);

  printf("a>%s\n", bignum_to_string(element_as_bignum(dictionary_get_pointer(dict, "bob"))));
  dictionary_forget(dict, "bob");
  printf("b>%s\n", bignum_to_string(element_as_bignum(dictionary_get_pointer(dict, "bob"))));
  dictionary_forget(dict, "bob");
  printf("c>%s\n", bignum_to_string(element_as_bignum(dictionary_get_pointer(dict, "bob"))));

  
  //printf(">%d<\n", testa->kind);

  //printf("a>%lu\n", bignum_to_string(element_as_bignum()));

  /*
  dictionary_forget(dict, "bob");
  printf("b>%lu\n", dictionary_has_key(dict, "bob"));
  dictionary_forget(dict, "bob");
  printf("c>%lu\n", dictionary_has_key(dict, "bob"));
  dictionary_forget_all(dict, "bob");
  printf("d>%lu\n", dictionary_has_key(dict, "bob"));
  */

  /*
  printf("%lu\n", dictionary_has_key(dict, "carl"));
  printf("a>%lu\n", dictionary_has_key(dict, "bob"));
  dictionary_forget(dict, "bob");
  printf("b>%lu\n", dictionary_has_key(dict, "bob"));
  dictionary_forget(dict, "bob");
  printf("c>%lu\n", dictionary_has_key(dict, "bob"));
  dictionary_forget_all(dict, "bob");
  printf("d>%lu\n", dictionary_has_key(dict, "bob"));
  */


  // printf("Aloha, edit \"src/main.c\" to get started\n");

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }