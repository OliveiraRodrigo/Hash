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
        //printf("\n[%c] h: '%u'", key[i], h);
    }
    h = h%tableSize;
    printf("\nh final: '%u'\n", h);
    return h;
    
}

int hashTable(int function, char key[151], int data){
    
    static unsigned int
        size = 0,
        maxSize = initialSize;
    
    static float
        trigger = initialSize * loadFactor;
    
    static cell
        *table;
    
    unsigned int
        i,    
        index,
        start,
        sizeTest;
    
    table = (cell*) malloc(initialSize * sizeof(cell));
    
    switch(function){
        
        case INSERT:
            index = hashFunction(key, maxSize);
            
            if(size == 0){
                
                for(i = 0; i < maxSize; i++){
                    table[i].filled = 0; //fazer isso tmb no rehash
                }
                
                strcpy(table[index].key, key);
                table[index].data = data;
                table[index].filled = 1;
                size++;
                return 0;
            }
            if(size + 1 >= trigger){
                hashTable(REHASH, key, data);
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
                    size++;
                    return 0;
                }
            }
            while(start != index);
            return -1;
            break;
            
        case SEARCH:
            index = hashFunction(key, maxSize);
            
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
            maxSize = maxSize * expansionFactor;
            trigger = maxSize * loadFactor;
            printf("\nRehash\n");
            printf("maxSize: %u\n", maxSize);
            printf("trigger: %f\n", trigger);
            break;
    }
    return 0;
}
