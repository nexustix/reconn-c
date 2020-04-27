#ifndef RECONN_UTIL_H
#define RECONN_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// harmless info
void rcn_info(char* message);

// cautionary warning
void rcn_warn(int test, char* message);

// fatal error
void rcn_error(int test, char* message);

// lobs last element of string by turning separator to 0
void rcn_seplob(char* cstring, char sep);

#endif