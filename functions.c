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

int linearInsert(cell* table, unsigned int size, char key[151], int data){
    
    unsigned int index, start;
    
    index = hashFunctionA(key, size);
    
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
            return 0;
        }
    }
    while(start != index);
    
    return -1;
}

int linkedInsert(linkedCell* table, unsigned int size, char key[151], int data){
    
    unsigned int index;
    node *test;
    
    index = hashFunctionA(key, size);
    
    if(table[index].filled){ //ocupada
        test = (node*) malloc (sizeof(node));
        test = table[index].first->next;
        while(1){
            if(test == NULL){
                test = (node*) malloc (sizeof(node));
                strcpy(test->key, key);
                test->data = data;
                test->next = NULL;
                break;
            }
            else{
                test = test->next;
            }
        }
    }
    else{
        table[index].filled = 1;
        table[index].first = (node*) malloc(sizeof(node));
        strcpy(table[index].first->key, key);
        table[index].first->data = data;
        table[index].first->next = NULL;
        return 0;
    }
    
    return -1;
}

int linearSearch(cell* table, unsigned int size, char key[151]){
    
    unsigned int index, start;
    
    index = hashFunctionA(key, size);
    
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
            if(index < size){
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

int linearRehash(cell* table, unsigned int size, char key[151], int data){
    
    unsigned int oldSize, i;
    cell *tempTable;
    
    oldSize = size / expansionFactor;
    
    tempTable = (cell*) malloc(oldSize * sizeof(cell));
    for(i = 0; i < oldSize; i++){
        if(table[i].filled){
            strcpy(tempTable[i].key, table[i].key);
            tempTable[i].data = table[i].data;
            tempTable[i].filled = 1;
            table[i].filled = 0;
        }
    }
    i = oldSize;
    while(i < size){
        table[i].filled = 0;
        //printf("%d\n", i);
        i++;
    }
    
    for(i = 0; i < oldSize; i++){
        if(tempTable[i].filled){
            if(linearInsert(table, size, table[i].key, table[i].data) == -1){
                //printf("Erro: %d\n", i);
                return -1;
            }
            else{
                //printf("OK: %d\n", i);
            }
        }
    }
    
    if(linearInsert(table, size, key, data) == 0){
        //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
        return 0;
    }
    
    return -1;
}
