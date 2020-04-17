#ifndef HASH_H
#define HASH_H


unsigned long hash_string(char *string){
    unsigned long hash = 0;
    int c;

    while (c = *string++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}


#endif