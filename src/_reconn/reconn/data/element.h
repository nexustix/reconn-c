#ifndef RECONN_DATA_ELEMENT_H
#define RECONN_DATA_ELEMENT_H

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "../util.h"

typedef enum {
  /*00*/ RECONN_ELEMENT_VOID,   // uninitialized
  /*01*/ RECONN_ELEMENT_EMPTY,  // ready for contents
  /*02*/ RECONN_ELEMENT_BIGNUM,
  /*03*/ RECONN_ELEMENT_I8,
  /*04*/ RECONN_ELEMENT_I16,
  /*05*/ RECONN_ELEMENT_I32,
  /*06*/ RECONN_ELEMENT_U8,
  /*07*/ RECONN_ELEMENT_U16,
  /*08*/ RECONN_ELEMENT_U32,
  /*09*/ RECONN_ELEMENT_WORD_PRIMARY,
  /*10*/ RECONN_ELEMENT_WORD_SECONDARY,
  /*11*/ RECONN_ELEMENT_ENUM,
  /*12*/ RECONN_ELEMENT_CSTRING,
} ReconnElementKind;

typedef struct ReconnElement {
  ReconnElementKind kind;
  void* data;
  char* id;
} ReconnElement;

ReconnElement* rcn_newReconnElement();

/* functions to turn element properties into string representations */

const char* rcn_element_data_to_cstring(ReconnElement* self);
const char* rcn_element_kind_to_cstring(ReconnElement* self);
int rcn_element_to_boolean(ReconnElement* self);

// uintmax_t rcn_element_to_uintmax(ReconnElement* self);
// intmax_t rcn_element_to_intmax(ReconnElement* self);

/*functions for testing data types*/

int rcn_element_is_signed_integer(ReconnElement* self);
int rcn_element_is_unsigned_integer(ReconnElement* self);
int rcn_element_is_integer(ReconnElement* self);

/* function for getting/setting various types */

int* rcn_element_get_enum(ReconnElement* self);
ReconnElement* rcn_element_set_enum(ReconnElement* destination, int* source);

const char* rcn_element_get_cstring(ReconnElement* self);
ReconnElement* rcn_element_set_cstring(ReconnElement* destination,
                                       const char* source);

/* functions for setting ints */

void rcn_element_set_i8(ReconnElement* self, char* value);
void rcn_element_set_i16(ReconnElement* self, short* value);
void rcn_element_set_i32(ReconnElement* self, long* value);

void rcn_element_set_u8(ReconnElement* self, unsigned char* value);
void rcn_element_set_u16(ReconnElement* self, unsigned short* value);
void rcn_element_set_u32(ReconnElement* self, unsigned long* value);

/* Functions for taking ints */

char rcn_element_take_i8(ReconnElement* self, int cleanup);
short rcn_element_take_i16(ReconnElement* self, int cleanup);
long rcn_element_take_i32(ReconnElement* self, int cleanup);

unsigned char rcn_element_take_u8(ReconnElement* self, int cleanup);
unsigned short rcn_element_take_u16(ReconnElement* self, int cleanup);
unsigned long rcn_element_take_u32(ReconnElement* self, int cleanup);

#endif