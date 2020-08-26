#ifndef RECONN_DATA_NUMBER_H
#define RECONN_DATA_NUMBER_H

#include <assert.h>
//#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 18,446,744,073,709,551,615
// 18446744073709551615
// 9,223,372,036,854,775,807
// 9223372036854775807

static const long long scales[19] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
    10000000000,
    100000000000,
    1000000000000,
    10000000000000,
    100000000000000,
    1000000000000000,
    10000000000000000,
    100000000000000000,
    1000000000000000000,
    // 10000000000000000000,
};

typedef struct ReconnNumber {
  long long data;
  char point;
} ReconnNumber;

ReconnNumber reconn_makeNumber(long long data, char point) {
  ReconnNumber self;
  self.data = data;
  self.point = point;
  return self;
}

ReconnNumber reconn_number_from_double(double value) {
  char raw[22] = {0};
  int past_dot = 0;
  int dot = 0;
  sprintf(raw, "%lf", value);
  const int len = strlen(raw);

  for (int i = 0; i < len; i++) {
    if (raw[i] == '.') {
      past_dot = 1;
    }
    if (past_dot) {
      dot += 1;
    }
  }

  double ddata = value * (double)scales[dot];
  return reconn_makeNumber((long long)ddata, dot);
}

double reconn_number_to_double(ReconnNumber *self) {
  return (double)self->data / (double)scales[abs(self->point)];
}

void reconn_number_print(ReconnNumber *self) {
  char raw[24] = {0};
  char str[24] = {0};
  unsigned char cursor = 0;

  sprintf(raw, "%lli", self->data);
  size_t len = strlen(raw);
  int dot = abs(self->point);

  for (int i = 0; i < len; i++) {
    if (len - i == dot) {
      str[cursor] = '.';
      cursor++;
    }
    str[cursor] = raw[i];
    cursor++;
  }
  str[cursor] = 0;
  cursor++;

  printf("%s\n", str);
}

void reconn_number_shift_point(ReconnNumber *self, char amount) {
  self->point += amount;
  assert(self->point >= 0);
}
void reconn_number_set_point(ReconnNumber *self, char dot) {
  assert(dot >= 0);
  self->point = dot;
}
#endif