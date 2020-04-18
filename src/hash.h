#ifndef HASH_H
#define HASH_H

unsigned long hash_cstring_sdbm(char *string) {
  unsigned long hash = 0;
  int c;

  while (c = *string++)
    hash = c + (hash << 6) + (hash << 16) - hash;

  return hash;
}

// unsigned long hash_cstring_djb2(unsigned char *str) {
//  unsigned long hash = 5381;
//  int c;
//
//  while (c = *str++)
//    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
//
//  return hash;
//}

unsigned long hash_cstring(char *string, unsigned long bucket_count) {
  return hash_cstring_sdbm(string) % bucket_count;
}

#endif