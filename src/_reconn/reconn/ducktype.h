#ifndef RECONN_DUCKTYPE_H
#define RECONN_DUCKTYPE_H

#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "data/element.h"

ReconnElement *rcn_ducktype_as_string(const char *token, int remove_quotes);

ReconnElement *rcn_ducktype_as_quote(const char *token, int remove_quotes);

ReconnElement *rcn_ducktype_as_number(const char *token, int base);

ReconnElement *rcn_ducktype_as_whatever(const char *token, int base);

#endif