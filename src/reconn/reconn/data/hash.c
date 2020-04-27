#include "reconn/data/hash.h"

unsigned long rcn_hash_cstring_djb2(const unsigned char* str) {
  unsigned long hash = 5381;
  int c;

  while (c = *str++) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

unsigned long rcn_hash_cstring_sdbm(const unsigned char* string) {
  unsigned long hash = 0;
  int c;

  while (c = *string++) hash = c + (hash << 6) + (hash << 16) - hash;

  return hash;
}

unsigned long rcn_hash_cstring(const char* string, unsigned long bucket_count) {
  switch (bucket_count) {
    case 0xf:
    case 0xff:
    case 0xfff:
    case 0xffff:
      return rcn_hash_cstring_sdbm((unsigned char*)string) & bucket_count;
      break;
    default:
      return rcn_hash_cstring_sdbm((unsigned char*)string) % bucket_count;
      break;
  }
}