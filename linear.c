#include "hash.h"
#include <string.h>

int linearInsert(cell* table, unsigned int maxSize, char key[151], int data){
    
    unsigned int index, start;
    
    index = hashFunctionA(key, maxSize);
    
    maxSize--;
    start = index;
    do{
        if(table[index].filled){ //ocupada
            if(!strcmp(table[index].key, key)){
                table[index].data = data;
                return 0;
            }
            if(index < maxSize){
                index++;
            }
            else{
                index = 0;
            }
        }
        else{
            strcpy(table[index].key, key);
            table[index].data = data;
            table[index].filled = True;
            return 1;
        }
    }
    while(start != index);
    
    return 0;
}

int linearSearch(cell* table, unsigned int maxSize, char key[151]){
    
    unsigned int index, start;
    
    index = hashFunctionA(key, maxSize);
    
    maxSize--;
    start = index;
    do{
        if(table[index].filled){
            if(strcmp(table[index].key, key)){
                if(index < maxSize){
                    index++;
                }
                else{
                    index = 0;
                }
            }
            else{
                return table[index].data;
            }
        }
        else{
            if(index < maxSize){
                index++;
            }
            else{
                index = 0;
            }
        }
    }
    while(start != index);
    
    return -1;
}

int linearRehash(cell* table[2], short alt, unsigned int maxSize, char key[151], int data){
    
    unsigned int oldSize, i;
    
    for(i = 0; i < maxSize; i++){
        table[alt][i].filled = False;
    }
    
    oldSize = maxSize / expansionFactor;
    
    for(i = 0; i < oldSize; i++){
        if(table[!alt][i].filled){
            linearInsert(table[alt], maxSize, table[!alt][i].key, table[!alt][i].data);
            //printf("OK: %d\n", i);
        }
    }
    
    //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
    if(linearInsert(table[alt], maxSize, key, data)){
        return 1;
    }
    return 0;
}
