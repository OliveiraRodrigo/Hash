/* 
 * File:   hash.c
 * Author: Rodrigo Oliveira
 *
 * Created on 17 de Dezembro de 2013, 15:47
 */

#include "hash.h"

int insert(cell* table, unsigned int size, char key[151], int data){
    
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

int search(cell* table, unsigned int size, char key[151]){
    
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

unsigned int hashFunction(char key[151], unsigned int tableSize){
    
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

int hashTable(int function, char key[151], int data){
    
    static unsigned int maxSize = 100;
    static unsigned int size = 0;
    cell * table = malloc(maxSize*sizeof(cell));
    unsigned int index, start;
    unsigned int sizeTest;
    
    switch(function){
        
        case INSERT:
            index = hashFunction(key, size);
            
            if(size == 0){
                strcpy(table[index].key, key);
                table[index].data = data;
                table[index].filled = 1;
                return 0;
            }
            
            sizeTest = size - 1;
            start = index;
            do{
                if(table[index].filled){ //ocupada
                    if(index < sizeTest){
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
                    return 0;
                }
            }
            while(start != index);
            return -1;
            break;
            
        case SEARCH:
            index = hashFunction(key, size);
            
            if(size == 0){
                return -1;
            }
            
            sizeTest = size - 1;
            start = index;
            do{
                if(table[index].filled){
                    if(strcmp(table[index].key, key)){
                        if(index < sizeTest){
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
            break;
            
        case REHASH:
            printf("\nrehash\n");
            break;
    }
    return 0;
}
