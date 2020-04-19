#include <stdio.h>

#include "bignum.h"
#include "dictionary.h"
#include "element.h"
#include "list.h"

int main(int argc, const char* argv[]) {
  /*
  unsigned char number1[5] = {1, 2, 3, 4, 5};
  Bignum* uno = bignum_from_chars(10, sizeof(number1), number1);
  uno->negative = 0;

  unsigned char number2[3] = {4, 5, 1};
  Bignum* due = bignum_from_chars(10, sizeof(number2), number2);
  due->negative = 0;
  */

  /*
  unsigned char number1[5] = {1, 2, 3, 4, 5};
  unsigned char number2[3] = {4, 5, 1};

  Dictionary* dict = newDictionary(4);

  Element* ele = newElement();

  dictionary_add(
      dict, "bob",
      element_set_bignum(ele, bignum_from_chars(10, sizeof(number1), number1)));
  dictionary_add(
      dict, "bob",
      element_set_bignum(ele, bignum_from_chars(10, sizeof(number2), number2)));
  dictionary_add(
      dict, "bob",
      element_set_bignum(ele, bignum_from_chars(10, sizeof(number1), number1)));
  free(ele);

  printf("a>%s\n",
         bignum_to_cstring(element_get_bignum(dictionary_get(dict, "bob"))));
  dictionary_forget(dict, "bob");
  printf("b>%s\n",
         bignum_to_cstring(element_get_bignum(dictionary_get(dict, "bob"))));
  dictionary_forget(dict, "bob");
  printf("c>%s\n",
         bignum_to_cstring(element_get_bignum(dictionary_get(dict, "bob"))));

  */

  Dictionary* dict = newDictionary(4);
  Element* e = newElement();

  dictionary_add(dict, "testa", element_set_cstring(e, "Hello, world"));

  printf(">%s<\n", element_get_cstring(dictionary_get(dict, "testa")));

  // printf("Aloha, edit \"src/main.c\" to get started\n");

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char* argv[]) { return main(argc, argv); }