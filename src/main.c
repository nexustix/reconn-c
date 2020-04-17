#include <stdio.h>

#include <stdio.h>
#include "bignum.h"
#include "list.h"

int main(int argc, const char *argv[]) {
  unsigned char number1[5] = {1,0,0,0,0};
  Bignum *uno = bignum_from_chars(10, sizeof(number1), number1);
  uno->negative = 0;

  unsigned char number2[1] = {1};
  Bignum *due = bignum_from_chars(10, sizeof(number2), number2);
  due->negative = 0;

  Bignum *r = newBignum(10, 0);

  bignum_add(r, uno, due);
  printf("+ >%s<\n", bignum_to_string(r));

  bignum_sub(r, uno, due);
  printf("- >%s<\n", bignum_to_string(r));

  
  List *stack = newList(8);
  list_push(stack, uno);
  Bignum *cake = newBignum(10, 0);
  
  list_pop(stack, cake);
  cake->digits[0] = 7;
  uno->digits[0] = 8;

  printf(">%s<\n", bignum_to_string(cake));
  printf(">%s<\n", bignum_to_string(uno));
  

  // Bignum *whatever = &stack->elements[stack->top];
  

  /*
  Bignum *tre = newBignum(10, 0);
  printf("U >%s<\n", bignum_to_string(uno));
  printf("T >%s<\n", bignum_to_string(tre));
  copyBignum(tre, uno);

  printf("U >%s<\n", bignum_to_string(uno));
  printf("T >%s<\n", bignum_to_string(tre));
  
  tre->digits[0] = 7;

  printf("U >%s<\n", bignum_to_string(uno));
  printf("T >%s<\n", bignum_to_string(tre));
  */
  
  


  // printf("Aloha, edit \"src/main.c\" to get started\n");

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }