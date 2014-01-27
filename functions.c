#include "hash.h"
#include <string.h>

unsigned int hashFunctionA(string key, unsigned int maxSize){
    
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

unsigned int hashFunction(string s, unsigned int maxSize){
    
    int slice = 4;
    int sLength = strlen(s);
    int intLength = sLength / slice;
    int cLength;
    int i, j, k;
    char c[slice+1];
    double sum = 0, mult = 1;
    unsigned int usum;
    
    for(j = 0; j < intLength; j++){
        sprintf(c, "%c", s[j*slice]);
        for(i = 1; i < slice; i++){
            sprintf(c, "%s%c", c, s[i+ j*slice]);
        }
        mult = 1;
        for (k = 0; k < slice; k++) {
	    sum += c[k] * mult;
            mult *= 256;
        }
    }
    
    //o resto da string (para nao multiplos de 4)
    i = intLength * slice;
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

unsigned int RSHash(char* str, unsigned int maxSize)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;
   
   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash % maxSize;
}
/* End Of RS Hash Function */


unsigned int JSHash(char* str, unsigned int maxSize)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash % maxSize;
}
/* End Of JS Hash Function */


unsigned int PJWHash(char* str, unsigned int maxSize)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash              = 0;
   unsigned int test              = 0;
   unsigned int i                 = 0;

   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash << OneEighth) + (*str);

      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash % maxSize;
}
/* End Of  P. J. Weinberger Hash Function */


unsigned int ELFHash(char* str, unsigned int maxSize)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash << 4) + (*str);
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash % maxSize;
}
/* End Of ELF Hash Function */


unsigned int BKDRHash(char* str, unsigned int maxSize)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash * seed) + (*str);
   }

   return hash % maxSize;
}
/* End Of BKDR Hash Function */


unsigned int SDBMHash(char* str, unsigned int maxSize)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash % maxSize;
}
/* End Of SDBM Hash Function */


unsigned int DJBHash(char* str, unsigned int maxSize)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash % maxSize;
}
/* End Of DJB Hash Function */


unsigned int DEKHash(char* str, unsigned int maxSize)
{
   unsigned int len = strlen(str);

   unsigned int hash = len;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }
   return hash % maxSize;
}
/* End Of DEK Hash Function */


unsigned int BPHash(char* str, unsigned int maxSize)
{
   unsigned int hash = 0;
   unsigned int i    = 0;
   
   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash = hash << 7 ^ (*str);
   }

   return hash % maxSize;
}
/* End Of BP Hash Function */


unsigned int FNVHash(char* str, unsigned int maxSize)
{
   const unsigned int fnv_prime = 0x811C9DC5;
   unsigned int hash      = 0;
   unsigned int i         = 0;

   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash *= fnv_prime;
      hash ^= (*str);
   }

   return hash % maxSize;
}
/* End Of FNV Hash Function */


unsigned int APHash(char* str, unsigned int maxSize)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   unsigned int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash % maxSize;
}
/* End Of AP Hash Function */
