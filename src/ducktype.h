#ifndef DUCKTYPE_H
#define DUCKTYPE_H

#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "element.h"

Element *ducktype_as_string(const char *token, int remove_quotes) {
  unsigned long length = strlen(token);
  char *result = (char *)malloc(length);
  // printf(">%c< >%c<\n", token[0], token[length - 1]);
  if ((length >= 2) && (token[0] == '"' && '"' == token[length - 1])) {
    Element *e = newElement();
    if (remove_quotes) {
      if (length == 2) {
        element_set_cstring(e, "");
      } else {
        // char *result = (char *)malloc(length - 2);
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

Element *ducktype_as_quote(const char *token, int remove_quotes) {
  unsigned long length = strlen(token);
  char *result = (char *)calloc(length, 1);

  if (length >= 1 && token[0] == ':') {
    Element *e = newElement();
    if (remove_quotes) {
      if (length == 1) {
        element_set_cstring(e, "");
        return e;
      } else {
        strncpy(result, token + 1, length + 2);
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
}

Element *ducktype_as_number(const char *token, int base) {
  int is_signed = (token[0] == '-' || token[0] == '+');
  char *endptr;

  // handle number being 0
  if (strcmp(token, "0") == 0) {
    Element *e = newElement();
    // element_give_u8(e, 0);
    return e;
  } else if ((strcmp(token, "+0") == 0) || (strcmp(token, "-0") == 0)) {
    Element *e = newElement();
    // element_give_i8(e, 0);
    return e;
  }

  if (is_signed) {
    intmax_t number = strtoimax(token, &endptr, base);
    if (number) {
      Element *e = newElement();
      if (labs(number) <= INT8_MAX) {
        char *v = (char *)calloc(1, sizeof(char));
        *v = number;
        element_set_i8(e, v);
      } else if (labs(number) <= INT16_MAX) {
        short *v = (short *)calloc(1, sizeof(short));
        *v = number;
        element_set_i16(e, v);
      } else if (labs(number) <= INT32_MAX) {
        long *v = (long *)calloc(1, sizeof(long));
        *v = number;
        element_set_i32(e, v);
      } else if (labs(number) <= INT64_MAX) {
        error(0, "64 bit integer support not implemented");
      } else {
        error(0, "number too large for maximum integer type");
      }
      return e;
    }

  } else {
    uintmax_t number = strtoumax(token, &endptr, base);
    if (number) {
      Element *e = newElement();
      if (number <= UINT8_MAX) {
        unsigned char *v = (unsigned char *)calloc(1, sizeof(unsigned char));
        *v = number;
        element_set_u8(e, v);
      } else if (number <= UINT16_MAX) {
        unsigned short *v = (unsigned short *)calloc(1, sizeof(unsigned short));
        *v = number;
        element_set_u16(e, v);
      } else if (number <= UINT32_MAX) {
        unsigned long *v = (unsigned long *)calloc(1, sizeof(unsigned long));
        *v = number;
        element_set_u32(e, v);
      } else if (number <= UINT64_MAX) {
        error(0, "64 bit unsigned integer support not implemented");
      } else {
        error(0, "number too large for maximum unsigned integer type");
      }
      return e;
    }
  }
  return NULL;
}

Element *ducktype_as_whatever(const char *token, int base) {
  Element *e = NULL;
  e = ducktype_as_quote(token, 1);
  if (e) return e;
  e = ducktype_as_string(token, 1);
  if (e) return e;
  // e = ducktype_as_bignum(token, 10);
  // if (e) return e;
  e = ducktype_as_number(token, base);
  if (e) return e;
  return NULL;
};

#endif