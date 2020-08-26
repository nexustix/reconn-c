#ifndef RECONN_DATA_DUCKTYPE_H
#define RECONN_DATA_DUCKTYPE_H

#include "buffer.h"
//#include "buffer_number.h"
#include "buffer_float.h"
#include "buffer_int.h"
#include "buffer_string.h"
#include "number.h"
//#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

// extern int errno;

// TODO rewrite
int reconn_ducktype_as_string(ReconnBuffer *buffer, const char *token,
                              int remove_quotes) {
  unsigned long length = strlen(token);
  char *result = (char *)calloc(length + 1 + 8, 1);
  // printf(">%c< >%c<\n", token[0], token[length - 1]);
  if ((length >= 2) && (token[0] == '"' && '"' == token[length - 1])) {
    // ReconnElement *e = rcn_newReconnElement();
    if (remove_quotes) {
      if (length == 2) {
        // FIXME pointer might get invalidated
        // rcn_element_set_cstring(e, "");
        reconn_buffer_push_cstring(buffer, "");
        free(result);
        return 1;
      } else {
        // char *result = (char *)malloc(length - 2);
        // strncpy(result, token + 1, length - 2);
        memcpy(result, token + 1, length - 2);
        // result[length] = 0;
        // printf("A >%lu< >%s<\n", length, result);
        // rcn_element_set_cstring(e, result);
        reconn_buffer_push_cstring(buffer, result);
        free(result);
        return 1;
      }
    } else {
      // strncpy(result, token, length);
      memcpy(result, token, length);
      // printf("B >%s<\n", result);
      // rcn_element_set_cstring(e, result);
      reconn_buffer_push_cstring(buffer, result);
      free(result);
      return 1;
    }
    // free(e);
  }
  free(result);
  return 0;
};

// TODO rewrite
int reconn_ducktype_as_quote(ReconnBuffer *buffer, const char *token,
                             int remove_quotes) {
  unsigned long length = strlen(token);
  char *result = (char *)calloc(length + 1 + 8, 1);

  if (length >= 1 && token[0] == ':') {
    // ReconnElement *e = rcn_newReconnElement();
    if (remove_quotes) {
      if (length == 1) {
        // rcn_element_set_cstring(e, "");
        reconn_buffer_push_cstring(buffer, "");
        free(result);
        return 1;
      } else {
        // strncpy(result, token + 1, length + 2);
        memcpy(result, token + 1, length + 2);
        // printf("C %s<\n", result);
        // rcn_element_set_cstring(e, result);
        reconn_buffer_push_cstring(buffer, result);
        free(result);
        return 1;
      }
    } else {
      // strncpy(result, token, length);
      memcpy(result, token, length);
      // printf("D >%s<\n", result);
      // rcn_element_set_cstring(e, result);
      reconn_buffer_push_cstring(buffer, result);
      free(result);
      return 1;
    }
    // free(e);
  }
  free(result);
  return 0;
}

int reconn_ducktype_as_int(ReconnBuffer *buffer, const char *token, int base) {
  // printf("NUMBRTEST\n");
  errno = 0;
  int is_signed = (token[0] == '-' || token[0] == '+');
  char *endptr = NULL;

  // handle number being 0
  if (strcmp(token, "0") == 0) {
    reconn_buffer_push_u8(buffer, 0);
    return 1;
  } else if ((strcmp(token, "+0") == 0) || (strcmp(token, "-0") == 0)) {
    // reconn_buffer_push_number(buffer, reconn_makeNumber(0, 0));
    reconn_buffer_push_s8(buffer, 0);
    return 1;
  }

  if (is_signed) {
    // printf("SIG\n");
    // intmax_t number = strtoimax(token, &endptr, base);
    long long number = strtoq(token, &endptr, base);
    if (!errno && !*endptr) {
      // ReconnElement *e = rcn_newReconnElement();
      if (CHAR_MIN <= number && number <= CHAR_MAX) {
        reconn_buffer_push_s8(buffer, number);
        return 1;
      } else if (SHRT_MIN <= number && number <= SHRT_MAX) {
        reconn_buffer_push_s16(buffer, number);
        return 1;
      } else if (LONG_MIN <= number && number <= LONG_MAX) {
        reconn_buffer_push_s32(buffer, number);
        return 1;
      } else if (LLONG_MIN <= number && number <= LLONG_MAX) {
        reconn_buffer_push_s64(buffer, number);
        return 1;
      } else {
        // rcn_error(0, "number too large for maximum integer type");
        // printf("ASDFS\n");
        return 0;
      }
    }

  } else {

    // uintmax_t number = strtoumax(token, &endptr, base);
    unsigned long long number = strtouq(token, &endptr, base);
    // printf("USIG >%s< >%llu< >%s<\n", token, number, endptr);
    if (!errno && !*endptr) {
      if (number <= UCHAR_MAX) {
        reconn_buffer_push_u8(buffer, number);
        return 1;
      } else if (number <= USHRT_MAX) {
        reconn_buffer_push_u16(buffer, number);
        return 1;
      } else if (number <= ULLONG_MAX) {
        reconn_buffer_push_u32(buffer, number);
        return 1;
      } else if (number <= ULLONG_MAX) {
        reconn_buffer_push_u64(buffer, number);
        return 1;
      } else {
        // rcn_error(0, "number too large for maximum unsigned integer type");
        // printf("ASDFU\n");
        return 0;
      }
      return 1;
    }
  }
  return 0;
}

int reconn_ducktype_as_double(ReconnBuffer *buffer, const char *token) {
  errno = 0;
  char *endptr = NULL;
  double number = strtod(token, &endptr);
  if (!errno && !*endptr) {
    reconn_buffer_push_f64(buffer, number);
    return 1;
  }
  return 0;
}

// double

int reconn_ducktype_as_whatever(ReconnBuffer *buffer, const char *token) {
  return reconn_ducktype_as_quote(buffer, token, 1) ||
         reconn_ducktype_as_string(buffer, token, 1) ||
         reconn_ducktype_as_int(buffer, token, 10) ||
         reconn_ducktype_as_double(buffer, token);
}

#endif