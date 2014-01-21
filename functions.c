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

unsigned int hashFunction(char s[151], unsigned int /*tableSize*/M){
    
    int sLength = strlen(s);
    int intLength = sLength / 4;
    int cLength;
    int i, j, k;
    char c[151];
    double sum = 0, mult = 1;
    unsigned int usum;
    
    for(j = 0; j < intLength; j++){
        //c = s.substring(j * 4, (j * 4) + 4).toCharArray();
        sprintf(c, "%c", s[j*4]);
        for(i = 1; i < 4; i++){
            sprintf(c, "%s%c", c, s[i+ j*4]);
        }
        mult = 1;
        //cLength = strlen(c);
        for (k = 0; k < 4/*cLength*/; k++) {
	    sum += c[k] * mult;
            mult *= 256;
        }
    }
    
    //o resto da string (para não múltiplos de 4)
    i = intLength * 4;
    sprintf(c, "%c", s[i]);
    for(i++; i < sLength; i++){
        sprintf(c, "%s%c", c, s[i]);
    }
    mult = 1;
    cLength = strlen(c);
    for (k = 0; k < cLength; k++) {
        sum += c[k] * mult;
        mult *= 256;
    }
    usum = (unsigned int) sum % M;
    //printf("\nsum:[%lf]\n", sum);
    printf("\nusum:[%u]\n", usum);
    return(usum);
}
