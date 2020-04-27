#ifndef RECONN_DATA_HASH_H
#define RECONN_DATA_HASH_H

unsigned long rcn_hash_cstring_djb2(const unsigned char* str);
unsigned long rcn_hash_cstring_sdbm(const unsigned char* string);

// hash cstring for dictionary with given bucket count
unsigned long rcn_hash_cstring(const char* string, unsigned long bucket_count);

#endif