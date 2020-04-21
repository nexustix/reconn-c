#ifndef DUCKTYPE_H
#define DUCKTYPE_H

#include <stdlib.h>
#include <string.h>

#include "element.h"

Element *ducktype_as_string(char *token, int remove_quotes) {
  unsigned long length = strlen(token);
  if ((length >= 2) && (token[0] == '"' == token[length - 1])) {
    Element *e = newElement();
    if (remove_quotes) {
      if (length == 2) {
        element_set_cstring(e, "");
      } else {
        char *result = (char *)malloc(length - 2);
        strncpy(result, token + 1, length - 2);
        element_set_cstring(e, result);
      }
    } else {
      element_set_cstring(e, token);
    }
  }
  return NULL;
};
int ducktype_as_bignum(char *token);
int ducktype_as_label(char *token);

Element *ducktype_as_whatever(char *token, int remove_quotes) {
  return ducktype_as_string(token, remove_quotes);
};

#endif