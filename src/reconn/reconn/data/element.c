#include "reconn/data/element.h"

ReconnElement* rcn_newReconnElement() {
  ReconnElement* self = (ReconnElement*)calloc(1, sizeof(*self));
  self->data = NULL;
  self->id = NULL;
  self->kind = RECONN_ELEMENT_EMPTY;
  return self;
}

int* rcn_element_get_enum(ReconnElement* self) { return (int*)self->data; }

ReconnElement* rcn_element_set_enum(ReconnElement* destination, int* source) {
  destination->data = (void*)source;
  destination->kind = RECONN_ELEMENT_ENUM;
  return destination;
}

const char* rcn_element_get_cstring(ReconnElement* self) {
  return (const char*)self->data;
}

ReconnElement* rcn_element_set_cstring(ReconnElement* destination,
                                       const char* source) {
  destination->data = (void*)source;
  destination->kind = RECONN_ELEMENT_CSTRING;
  return destination;
}

// functions for giving ints

void rcn_element_set_i8(ReconnElement* self, char* value) {
  // self->data = realloc(self->data, sizeof(char*));
  self->kind = RECONN_ELEMENT_I8;
  self->data = value;
}
void rcn_element_set_i16(ReconnElement* self, short* value) {
  self->kind = RECONN_ELEMENT_I16;
  self->data = value;
}
void rcn_element_set_i32(ReconnElement* self, long* value) {
  self->kind = RECONN_ELEMENT_I32;
  self->data = value;
}
void rcn_element_set_u8(ReconnElement* self, unsigned char* value) {
  self->kind = RECONN_ELEMENT_U8;
  self->data = value;
}
void rcn_element_set_u16(ReconnElement* self, unsigned short* value) {
  self->kind = RECONN_ELEMENT_U16;
  self->data = value;
}
void rcn_element_set_u32(ReconnElement* self, unsigned long* value) {
  self->kind = RECONN_ELEMENT_U32;
  self->data = value;
}

// Functions for taking ints

char rcn_element_take_i8(ReconnElement* self, int cleanup) {
  char r = 0;
  switch (self->kind) {
    case RECONN_ELEMENT_I8:
      r = (char)*(char*)self->data;
      break;
    case RECONN_ELEMENT_I16:
      r = (char)*(short*)self->data;
      break;
    case RECONN_ELEMENT_I32:
      r = (char)*(long*)self->data;
      break;
    case RECONN_ELEMENT_U8:
      r = (char)*(unsigned char*)self->data;
      break;
    case RECONN_ELEMENT_U16:
      r = (char)*(unsigned short*)self->data;
      break;
    case RECONN_ELEMENT_U32:
      r = (char)*(unsigned long*)self->data;
      break;

    default:
      rcn_error(0, "unable to take i8");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

short rcn_element_take_i16(ReconnElement* self, int cleanup) {
  short r = 0;
  switch (self->kind) {
    case RECONN_ELEMENT_I8:
      r = (short)*(char*)self->data;
      break;
    case RECONN_ELEMENT_I16:
      r = (short)*(short*)self->data;
      break;
    case RECONN_ELEMENT_I32:
      r = (short)*(long*)self->data;
      break;
    case RECONN_ELEMENT_U8:
      r = (short)*(unsigned char*)self->data;
      break;
    case RECONN_ELEMENT_U16:
      r = (short)*(unsigned short*)self->data;
      break;
    case RECONN_ELEMENT_U32:
      r = (short)*(unsigned long*)self->data;
      break;

    default:
      rcn_error(0, "unable to take i16");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

long rcn_element_take_i32(ReconnElement* self, int cleanup) {
  long r = 0;
  switch (self->kind) {
    case RECONN_ELEMENT_I8:
      r = (long)*(char*)self->data;
      break;
    case RECONN_ELEMENT_I16:
      r = (long)*(short*)self->data;
      break;
    case RECONN_ELEMENT_I32:
      r = (long)*(long*)self->data;
      break;
    case RECONN_ELEMENT_U8:
      r = (long)*(unsigned char*)self->data;
      break;
    case RECONN_ELEMENT_U16:
      r = (long)*(unsigned short*)self->data;
      break;
    case RECONN_ELEMENT_U32:
      r = (long)*(unsigned long*)self->data;
      break;

    default:
      rcn_error(0, "unable to take i32");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

unsigned char rcn_element_take_u8(ReconnElement* self, int cleanup) {
  unsigned char r = 0;
  switch (self->kind) {
    case RECONN_ELEMENT_I8:
      r = (unsigned char)*(char*)self->data;
      break;
    case RECONN_ELEMENT_I16:
      r = (unsigned char)*(short*)self->data;
      break;
    case RECONN_ELEMENT_I32:
      r = (unsigned char)*(long*)self->data;
      break;
    case RECONN_ELEMENT_U8:
      r = (unsigned char)*(unsigned char*)self->data;
      break;
    case RECONN_ELEMENT_U16:
      r = (unsigned char)*(unsigned short*)self->data;
      break;
    case RECONN_ELEMENT_U32:
      r = (unsigned char)*(unsigned long*)self->data;
      break;

    default:
      rcn_error(0, "unable to take u8");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

unsigned short rcn_element_take_u16(ReconnElement* self, int cleanup) {
  unsigned short r = 0;
  switch (self->kind) {
    case RECONN_ELEMENT_I8:
      r = (unsigned short)*(char*)self->data;
      break;
    case RECONN_ELEMENT_I16:
      r = (unsigned short)*(short*)self->data;
      break;
    case RECONN_ELEMENT_I32:
      r = (unsigned short)*(long*)self->data;
      break;
    case RECONN_ELEMENT_U8:
      r = (unsigned short)*(unsigned char*)self->data;
      break;
    case RECONN_ELEMENT_U16:
      r = (unsigned short)*(unsigned short*)self->data;
      break;
    case RECONN_ELEMENT_U32:
      r = (unsigned short)*(unsigned long*)self->data;
      break;

    default:
      rcn_error(0, "unable to take u16");
      break;
  }
  if (cleanup) free(self->data);
  return r;
}

unsigned long rcn_element_take_u32(ReconnElement* self, int cleanup) {
  unsigned long r = 0;
  switch (self->kind) {
    case RECONN_ELEMENT_I8:
      r = (unsigned long)*(char*)self->data;
      break;
    case RECONN_ELEMENT_I16:
      r = (unsigned long)*(short*)self->data;
      break;
    case RECONN_ELEMENT_I32:
      r = (unsigned long)*(long*)self->data;
      break;
    case RECONN_ELEMENT_U8:
      r = (unsigned long)*(unsigned char*)self->data;
      break;
    case RECONN_ELEMENT_U16:
      r = (unsigned long)*(unsigned short*)self->data;
      break;
    case RECONN_ELEMENT_U32:
      r = (unsigned long)*(unsigned long*)self->data;
      break;

    default:
      rcn_error(0, "unable to take u32");
      break;
  }

  if (cleanup) free(self->data);
  return r;
}

const char* rcn_element_data_to_cstring(ReconnElement* self) {
  char* tmp_str;
  switch (self->kind) {
    case RECONN_ELEMENT_CSTRING:
      tmp_str = (char*)calloc(strlen((char*)self->data) + 1, sizeof(char));
      strcpy(tmp_str, (char*)self->data);
      return tmp_str;
      break;

    case RECONN_ELEMENT_I8:
      tmp_str = (char*)calloc(5, sizeof(char));
      sprintf(tmp_str, "%hhi", *(char*)self->data);
      return tmp_str;
      break;
    case RECONN_ELEMENT_I16:
      tmp_str = (char*)calloc(7, sizeof(short));
      sprintf(tmp_str, "%hi", *(short*)self->data);
      return tmp_str;
      break;
    case RECONN_ELEMENT_I32:
      tmp_str = (char*)calloc(22, sizeof(long));
      sprintf(tmp_str, "%li", *(long*)self->data);
      return tmp_str;
      break;
    case RECONN_ELEMENT_U8:
      tmp_str = (char*)calloc(5, sizeof(unsigned char));
      sprintf(tmp_str, "%hhu", *(unsigned char*)self->data);
      return tmp_str;
      break;
    case RECONN_ELEMENT_U16:
      tmp_str = (char*)calloc(7, sizeof(unsigned short));
      sprintf(tmp_str, "%hu", *(unsigned short*)self->data);
      return tmp_str;
      break;
    case RECONN_ELEMENT_U32:
      tmp_str = (char*)calloc(22, sizeof(unsigned long));
      sprintf(tmp_str, "%lu", *(unsigned long*)self->data);
      return tmp_str;
      break;

    default:
      rcn_error(0, "can't turn element value into string");
      break;
  }
  return "N/A";
}

const char* rcn_element_kind_to_cstring(ReconnElement* self) {
  switch (self->kind) {
    case RECONN_ELEMENT_CSTRING:
      return "string";
      break;

    case RECONN_ELEMENT_I8:
      return "i8";
      break;
    case RECONN_ELEMENT_I16:
      return "i16";
      break;
    case RECONN_ELEMENT_I32:
      return "i32";
      break;
    case RECONN_ELEMENT_U8:
      return "u8";
      break;
    case RECONN_ELEMENT_U16:
      return "u16";
      break;
    case RECONN_ELEMENT_U32:
      return "u32";
      break;

    default:
      return "???";
      break;
  }
}

int rcn_element_is_signed_integer(ReconnElement* self) {
  switch (self->kind) {
    case RECONN_ELEMENT_I8:
    case RECONN_ELEMENT_I16:
    case RECONN_ELEMENT_I32:
      return 1;
      break;

    default:
      return 0;
      break;
  }
}

int rcn_element_is_unsigned_integer(ReconnElement* self) {
  switch (self->kind) {
    case RECONN_ELEMENT_U8:
    case RECONN_ELEMENT_U16:
    case RECONN_ELEMENT_U32:
      return 1;
      break;

    default:
      return 0;
      break;
  }
}