#include "hash.h"
#include <string.h>

unsigned int hashFunction(string key, unsigned int maxSize){
    
    unsigned int i, h, keySize;
    
    h = 0;
    keySize = strlen(key);
    for(i = 0; i < keySize; i++){
        h += key[i]*31*keySize;
        //printf("\n[%c] h: '%u'", key[i], h);
    }
    h = h % maxSize;
    //printf("\nh final: '%u'\n", h);
    return h;
    
}

unsigned int DEKHash(string key, unsigned int maxSize){
    
    unsigned int len  = strlen(key);
    unsigned int hash = len;
    unsigned int i;
    
    for(i = 0; i < len; key++, i++){
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*key);
    }
    return hash % maxSize;
}
