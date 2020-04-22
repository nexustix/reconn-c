#ifndef BIGNUM_H
#define BIGNUM_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bignum{
  unsigned char* digits;
  int negative;          // is number negative (boolean)
  unsigned int last;     // index of last element
  unsigned int base;     // base of number
  unsigned int reserve;  // length reserved
} Bignum;

Bignum* newBignum(unsigned int base) {
  const unsigned int startlen = 8;
  Bignum* self = (Bignum*)calloc(1, sizeof(*self));
  self->digits = (unsigned char*)calloc(startlen, sizeof(char));
  self->negative = 0;
  self->last = 0;
  self->base = base;
  self->reserve = startlen;
  return self;
}

void bignum_resize(Bignum* self, unsigned int size) {
  self->digits = (unsigned char*)realloc(self->digits, size);
}

Bignum *bignum_copy_cstring(const char *cstring){
  size_t length = strlen(cstring);
  Bignum* self = newBignum(256);
  bignum_resize(self, length);
  //self->digits = (unsigned char*)cstring;
  self->digits = (unsigned char*)strcpy((char*)self->digits, cstring);
  self->negative = 0;
  self->last = length-1;
  //self->base = 256;
  return self;
}

/*
void oldBignum(Bignum* self, unsigned int base) {
  const unsigned int maxlen = 16;
  if (self->reserve > maxlen) {
    free(self->digits);
    self->digits = (unsigned char*)malloc(maxlen);
    self->reserve = maxlen;
  }  // else if(!self->reserve){
  //  self->digits = (unsigned char *)malloc(0);
  //  self->reserve = 0;
  //}
  self->negative = 0;
  self->last = 0;
  self->base = base;
}
*/

void dupBignum(Bignum* destination, Bignum* source) {
  // bignum_resize(destination, source->last+1);
  free(destination->digits);
  destination->digits = (unsigned char*)malloc(source->last + 1);
  memcpy(destination->digits, source->digits, source->last + 1);
  destination->negative = source->negative;
  destination->last = source->last;
  destination->base = source->base;
  destination->reserve = source->last + 1;
}

Bignum* bignum_from_chars(unsigned int base, unsigned int size,
                          unsigned char digits[]) {
  // Bignum *self = newBignum(base, size);
  Bignum* self = (Bignum*)calloc(1, sizeof(Bignum));
  bignum_resize(self, size);
  self->last = size - 1;
  for (unsigned int i = 0; i < size; i++) {
    self->digits[i] = digits[(size - 1) - i];
  }
  return self;
}

void bignum_clean_zeroes(Bignum* self) {
  for (unsigned int i = 0; i <= self->last; i++) {
    if (self->digits[self->last - i] == 0) {
      self->last--;
    } else {
      return;
    }
  }
}

void bignum_set_digit(Bignum* self, unsigned int index, unsigned char digit) {
  if (self->reserve < index + 1) {
    bignum_resize(self, index + 1);
  }
  self->digits[index] = digit;
  if (index > self->last) {
    self->last = index;
  }
}

const char* bignum_to_cstring(Bignum* self) {
  char* s;
  unsigned int pointer = 1;
  char* tmp = (char*)malloc(1);
  if (self->base > 10) {
    s = (char*)malloc(((self->last + 1) * 2) + 1 + 1);
  } else {
    s = (char*)malloc((self->last + 1) + 1 + 1);
  }

  if (self->negative) {
    s[0] = '-';
  } else {
    s[0] = '+';
  }

  if (self->base == 256){
    return (const char*)self->digits;
  } else if (self->base > 10) {
    for (unsigned int i = 0; i <= self->last; i++) {
      sprintf(tmp, "%d", self->digits[self->last - i]);
      s[pointer] = tmp[0];
      s[pointer + 1] = '|';
      pointer += 2;
    }
    s[((self->last + 1) * 2) + 1 + 1] = 0;
  } else {
    for (unsigned int i = 0; i <= self->last; i++) {
      sprintf(tmp, "%d", self->digits[self->last - i]);
      s[pointer] = tmp[0];
      pointer++;
    }
    s[(self->last + 1) + 1 + 1] = 0;
  }
  return s;
}

int bignum_smaller_abs(Bignum* a, Bignum* b) {
  if (a->last > b->last) {
    return 1;
  } else if (a->last < b->last) {
    return 0;
  } else {
    for (unsigned int i = 0; i <= a->last; i++) {
      if (a->digits[i] > b->digits[i]) {
        return 1;
      } else if (a->digits[i] < b->digits[i]) {
        return 0;
      }
    }
  }
  return 2;
}

void bignum_blind_add(Bignum* r, Bignum* a, Bignum* b) {
  // FIXME assert base 10
  if (bignum_smaller_abs(a, b)) {
    bignum_resize(r, a->last + 1);
    r->last = 0;
    int carry = 0;
    unsigned char na;
    unsigned char nb;
    unsigned char tmp;
    for (unsigned int i = 0; i <= a->last; i++) {
      na = i > a->last ? 0 : a->digits[i];
      nb = i > b->last ? 0 : b->digits[i];

      tmp = na + nb + carry;
      if (tmp > 10) {
        carry = 1;
        bignum_set_digit(r, i, tmp % 10);
      } else {
        carry = 0;
        bignum_set_digit(r, i, tmp);
      }
    }

  } else {
    bignum_blind_add(r, b, a);
  }
}

void bignum_blind_sub(Bignum* r, Bignum* a, Bignum* b) {
  // FIXME assert base 10
  if (bignum_smaller_abs(a, b)) {
    bignum_resize(r, a->last + 1);
    r->last = 0;
    int carry = 0;
    int na;
    int nb;
    for (unsigned int i = 0; i <= a->last; i++) {
      na = a->digits[i];
      nb = i > b->last ? 0 : b->digits[i];

      if (na - carry < nb) {
        bignum_set_digit(r, i, (na + 10 - carry) - nb);
        carry = 1;
      } else {
        bignum_set_digit(r, i, (na - carry) - nb);
        carry = 0;
      }
    }
    bignum_clean_zeroes(r);

  } else {
    bignum_blind_sub(r, b, a);
    r->negative = 1;
  }
}

void bignum_add(Bignum* r, Bignum* a, Bignum* b) {
  r->negative = 0;
  if (a->negative == b->negative) {
    if (!a->negative) {
      bignum_blind_add(r, a, b);
    } else {
      bignum_blind_add(r, a, b);
      r->negative = 1;
    }
  } else {
    if (!a->negative) {
      bignum_blind_sub(r, a, b);
    } else {
      bignum_blind_sub(r, b, a);
    }
  }
}

void bignum_sub(Bignum* r, Bignum* a, Bignum* b) {
  r->negative = 0;
  if (a->negative == b->negative) {
    if (!a->negative) {
      bignum_blind_sub(r, a, b);
    } else {
      bignum_blind_sub(r, b, a);
    }
  } else {
    if (!a->negative) {
      bignum_blind_add(r, a, b);
    } else {
      bignum_blind_add(r, a, b);
      r->negative = 1;
    }
  }
}

#endif