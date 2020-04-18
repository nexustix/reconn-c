#include <stdio.h>

#include <stdio.h>
#include "bignum.h"
#include "list.h"
#include "element.h"

int main(int argc, const char *argv[]) {

  unsigned char number1[5] = {1,2,3,4,5};
  Bignum *uno = bignum_from_chars(10, sizeof(number1), number1);
  uno->negative = 0;

  unsigned char number2[3] = {4,5,1};
  Bignum *due = bignum_from_chars(10, sizeof(number2), number2);
  due->negative = 0;

  /*
  Bignum *r = newBignum(10, 0);

  bignum_add(r, uno, due);
  printf("+ >%s<\n", bignum_to_string(r));

  bignum_sub(r, uno, due);
  printf("- >%s<\n", bignum_to_string(r));
  */

  /*
  List *list = newList(8);
  //Element *element = newElement();
  Bignum *tre = newBignum(10, 0);

  list_push_bignum(list, uno);
  list_push_bignum(list, due);
  printf(">%s<\n", bignum_to_string(uno));
  printf(">%s<\n", bignum_to_string(due));
  printf(">%s<\n", bignum_to_string(tre));
  list_pop_bignum(list, tre);
  printf(">%s<\n", bignum_to_string(uno));
  printf(">%s<\n", bignum_to_string(due));
  printf(">%s<\n", bignum_to_string(tre));
  list_pop_bignum(list, tre);
  printf(">%s<\n", bignum_to_string(uno));
  printf(">%s<\n", bignum_to_string(due));
  printf(">%s<\n", bignum_to_string(tre));
  tre->digits[0] = 7;
  printf(">%s<\n", bignum_to_string(uno));
  printf(">%s<\n", bignum_to_string(due));
  printf(">%s<\n", bignum_to_string(tre));
  */


  //element_of_bignum(element, uno);
  //list_push(list, element);
  //element_of_bignum(element, due);
  //list_push(list, element);
  //list_pop(list, element);
  //element_as_bignum(element, tre);
  //printf(">%s<\n", bignum_to_string(tre));
  //list_pop(list, element);
  //element_as_bignum(element, tre);
  //printf(">%s<\n", bignum_to_string(tre));
  
  
  // printf("Aloha, edit \"src/main.c\" to get started\n");

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }