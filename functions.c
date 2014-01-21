#include "hash.h"
#include <string.h>

unsigned int hashFunctionA(char key[151], unsigned int tableSize){
    
    unsigned int i, h, keySize;
    
    h = 0;
    keySize = strlen(key);
    for(i = 0; i < keySize; i++){
        h += key[i]*31*keySize;
        //printf("\n[%c] h: '%u'", key[i], h);
    }
    h = h%tableSize;
    //printf("\nh final: '%u'\n", h);
    return h;
    
}

unsigned int hashFunction(char key[151], unsigned int tableSize){
    return 0;
}
