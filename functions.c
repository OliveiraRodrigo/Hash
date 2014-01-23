#include "hash.h"
#include <string.h>

unsigned int hashFunctionA(char key[151], unsigned int maxSize){
    
    unsigned int i, h, keySize;
    
    h = 0;
    keySize = strlen(key);
    for(i = 0; i < keySize; i++){
        h += key[i]*31*keySize;
        //printf("\n[%c] h: '%u'", key[i], h);
    }
    h = h%maxSize;
    //printf("\nh final: '%u'\n", h);
    return h;
    
}

unsigned int hashFunction(char s[151], unsigned int maxSize){
    
    int sLength = strlen(s);
    int intLength = sLength / 4;
    int cLength;
    int i, j, k;
    char c[5];
    double sum = 0, mult = 1;
    unsigned int usum;
    
    for(j = 0; j < intLength; j++){
        sprintf(c, "%c", s[j*4]);
        for(i = 1; i < 4; i++){
            sprintf(c, "%s%c", c, s[i+ j*4]);
        }
        mult = 1;
        for (k = 0; k < 4; k++) {
	    sum += c[k] * mult;
            mult *= 256;
        }
    }
    
    //o resto da string (para nao multiplos de 4)
    i = intLength * 4;
    if(i < sLength){
        sprintf(c, "%c", s[i]);
    }
    for(i++; i < sLength; i++){
        sprintf(c, "%s%c", c, s[i]);
    }
    mult = 1;
    
    cLength = strlen(c);
    for (k = 0; k < cLength; k++) {
        sum += c[k] * mult;
        mult *= 256;
    }
    //printf("\r\n[%u %% %u]\r\n", (unsigned int) sum, M);
    usum = (unsigned int) sum % maxSize;
    //printf("[%u]\r\n", usum);
    //printf("\r\n[%u/%u]\r\n", usum, M);
    return usum;
}
