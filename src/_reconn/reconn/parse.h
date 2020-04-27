#ifndef RECONN_PARSE_H
#define RECONN_PARSE_H

#define QUOTE_CHAR '"'

#include <ctype.h>
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data/element.h"
#include "data/list.h"
#include "util.h"

unsigned int rcn_parse_string(char *data, unsigned int offset,
                              ReconnList *tokens);

void rcn_parse_tokens(char *data, ReconnList *tokens);

#endif