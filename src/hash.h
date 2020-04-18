#ifndef HASH_H
#define HASH_H


unsigned long hash_cstring_sdbm(char *string){
    unsigned long hash = 0;
    int c;

    while (c = *string++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

unsigned long hash_cstring(char* string){
    return hash_cstring_sdbm(string);
}

#endif