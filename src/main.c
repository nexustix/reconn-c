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

  Bignum *tre = newBignum(10, 0);
  //Element *element = newElement();
  List *list = newList(8);

  /*
  element_from_bignum(element, uno);
  element_to_bignum(element, tre);

  printf(">%s<\n", bignum_to_string(uno));
  printf(">%s<\n", bignum_to_string(tre));

  printf(">%s<\n", bignum_to_string(uno));
  printf(">%s<\n", bignum_to_string(tre));
  */

  
  list_push_bignum(list, due);
  list_push_bignum(list, uno);

  printf("A>%s<\n", bignum_to_string(uno));
  printf("A>%s<\n", bignum_to_string(due));
  printf("A>%s<\n", bignum_to_string(tre));
  list_pop_bignum(list, tre);
  printf("B>%s<\n", bignum_to_string(uno));
  printf("B>%s<\n", bignum_to_string(due));
  printf("B>%s<\n", bignum_to_string(tre));
  list_pop_bignum(list, tre);
  printf("C>%s<\n", bignum_to_string(uno));
  printf("C>%s<\n", bignum_to_string(due));
  printf("C>%s<\n", bignum_to_string(tre));
  tre->digits[0] = 7;
  printf("D>%s<\n", bignum_to_string(uno));
  printf("D>%s<\n", bignum_to_string(due));
  printf("D>%s<\n", bignum_to_string(tre));
  


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