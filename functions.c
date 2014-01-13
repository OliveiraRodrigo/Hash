/* 
 * File:   hash.c
 * Author: Rodrigo Oliveira
 *
 * Created on 17 de Dezembro de 2013, 15:47
 */

#include "hash.h"

int insert(cell* table, unsigned int size, char key[200], unsigned int data){
    
    unsigned int index, start;
    
    index = hashFunction(key, size);
    
    size--;
    start = index;
    do{
        if(table[index].filled){ //ocupada
            if(index < size){
                index++;
            }
            else{
                index = 0;
            }
        }
        else{
            strcpy(table[index].key, key);
            table[index].data = data;
            table[index].filled = 1;
            return 1;
        }
    }
    while(start != index);
    
    return 0;
}

unsigned int search(cell* table, unsigned int size, char key[200]){
    
    unsigned int index, start;
    
    index = hashFunction(key, size);
    
    size--;
    start = index;
    do{
        if(table[index].filled){
            if(strcmp(table[index].key, key)){
                if(index < size){
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
            index++;
        }
    }
    while(start != index);
    
    return -1;
}

unsigned int hashFunction(char key[200], unsigned int tableSize){
    
    unsigned int i, h, keySize;
    
    h = 0;
    keySize = strlen(key);
    for(i = 0; i < keySize; i++){
        h += key[i]*31*keySize;
        //printf("\n%c h: '%u'", key[i], h);
    }
    h = h%tableSize;
    //printf("\nhfinal: '%u'", h);
    //printf("\n");
    return h;
    
}
