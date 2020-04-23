#ifndef DUCKTYPE_H
#define DUCKTYPE_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#include "element.h"

Element *ducktype_as_string(const char *token, int remove_quotes) {
  unsigned long length = strlen(token);
  char *result = (char *)malloc(length);
  //printf(">%c< >%c<\n", token[0], token[length - 1]);
  if ((length >= 2) && (token[0] == '"' && '"' == token[length - 1])) {
    Element *e = newElement();
    if (remove_quotes) {
      if (length == 2) {
        element_set_cstring(e, "");
      } else {
        //char *result = (char *)malloc(length - 2);
        strncpy(result, token + 1, length - 2);
        element_set_cstring(e, result);
        return e;
      }
    } else {
      strncpy(result, token, length);
      element_set_cstring(e, result);
      return e;
    }
  }
  return NULL;
};

//HACK
Element *ducktype_as_bignum(const char *token, unsigned short base){
  size_t length = strlen(token);
  //unsigned short base = 10;
  Bignum *bn = newBignum(base);
  bignum_resize(bn, length);
  char cur = token[0];
  size_t index;

  unsigned char tmp_digit;
  char* endptr = NULL;
  char extractor[5] = {0,0,0,0,0};

  //size_t offset = 0;
  //if (cur == '+'){
  //  offset=1;
  //  bn->negative = 0;
  //}else if(cur == '-'){
  //  offset=1;
  //  bn->negative = 1;
  //}

  for (size_t i=0;i < length;i++){
    index = (length-1)-i;
    //index = i;
    //printf("%d<\n", (int)index);
    cur = token[index];
    if (cur == '0'){
      //bignum_set_digit(bn, index, 0);
      bignum_set_digit(bn, i, 0);
    }else{
      extractor[0] = cur;
      tmp_digit = (unsigned char)strtoumax(extractor, &endptr, base);
      if(tmp_digit){
        //bignum_set_digit(bn, index, tmp_digit);
        bignum_set_digit(bn, i, tmp_digit);
        //bignum_set_digit(bn, bn->last, tmp_digit);
      }else if (length > 1 && index==0){
        if (cur == '-'){
          bn->negative = 1;
        }else if (cur == '+'){
          bn->negative = 0;
        }else return NULL;
      }else{
        return NULL;
      }
    }
  }
  Element *e = newElement();
  bignum_clean_zeroes(bn);
  return element_set_bignum(e, bn);
}
int ducktype_as_label(const char *token);

Element *ducktype_as_whatever(const char *token, int remove_quotes) {
  Element *e = NULL;
  e = ducktype_as_string(token, remove_quotes);
  if (e) return e;
  e = ducktype_as_bignum(token, 10);
  if (e) return e;
  return NULL;
};

#endif