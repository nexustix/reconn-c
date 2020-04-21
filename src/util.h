#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

// harmless info
void info(char* message){
  fprintf( stderr, "<-> %s\n", message);
}

// cautionary warning
void warn(int test, char* message){
  if (!test){
    fprintf( stderr, "<!> WARN %s\n", message);
  }
}

// fatal error
void error(int test, char* message){
  if (!test){
    fprintf( stderr, "<!> FATAL %s\n", message);
    exit(1);
  }
}
#endif