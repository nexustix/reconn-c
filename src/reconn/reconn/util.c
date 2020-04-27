#include "reconn/util.h"

// harmless info
void rcn_info(char* message) { fprintf(stderr, "<-> %s\n", message); }

// cautionary warning
void rcn_warn(int test, char* message) {
  if (!test) {
    fprintf(stderr, "<!> WARN %s\n", message);
  }
}

// fatal error
void rcn_error(int test, char* message) {
  if (!test) {
    fprintf(stderr, "<!> FATAL %s\n", message);
    exit(1);
  }
}

// lobs last element of string by turning separator to 0
void rcn_seplob(char* cstring, char sep) {
  char* cut = strrchr(cstring, sep);
  if (cut) {
    cut[0] = 0;
  } else {
    cstring[0] = 0;
  }
}