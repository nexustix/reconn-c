#include "reconn/parse.h"

unsigned int rcn_parse_string(char *data, unsigned int offset,
                              ReconnList *tokens) {
  static ReconnElement *e;
  if (!e) e = rcn_newReconnElement();
  int quote_found = 0;
  unsigned int counter = 1;
  unsigned int max_length = strlen(data) - offset;
  unsigned char cur;
  char *buffer = (char *)calloc(max_length + 2, 1);
  buffer[0] = QUOTE_CHAR;
  for (unsigned int i = 1; i < max_length; i++) {
    cur = data[offset + i];
    if (cur == QUOTE_CHAR) {
      if (quote_found) {
        buffer[counter] = QUOTE_CHAR;
        counter++;
      }
      quote_found = !quote_found;
    } else {
      if (quote_found) {
        buffer[counter] = QUOTE_CHAR;
        rcn_list_push(tokens, rcn_element_set_cstring(e, buffer));
        return i;
      }
      buffer[counter] = cur;
      counter++;
    }
  }
  // TODO evaulate
  return 0;
}

void rcn_parse_tokens(char *data, ReconnList *tokens) {
  int inside_token = 0;
  unsigned int offset = 0;
  unsigned int size = 0;
  unsigned int length = strlen(data);
  char cur;
  char *buffer;

  for (unsigned int i = 0; i <= length; i++) {
    static ReconnElement *e;
    if (!e) e = rcn_newReconnElement();

    cur = data[i];
    if (isspace(cur) || !cur) {
      if (inside_token) {
        size++;
        // flush token
        buffer = (char *)calloc(size + 2, 1);
        strncpy(buffer, data + offset, size);
        rcn_list_push(tokens, rcn_element_set_cstring(e, buffer));
        offset = i;
      } else {
        offset++;
      }
      inside_token = 0;
    } else {
      if (inside_token) {
        size++;
      } else if (cur == QUOTE_CHAR) {
        size = rcn_parse_string(data, i, tokens);

        i += size;
        offset += size;
        size = 0;
        inside_token = 0;
        continue;
      } else {
        size = 0;
        offset = i;
      }

      inside_token = 1;
    }
  }
}