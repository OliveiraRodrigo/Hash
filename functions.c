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
            if(!strcmp(table[index].key, key)){
                table[index].data = data;
                return 0;
            }
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
            table[index].filled = True;
            return 1;
        }
    }
    while(start != index);
    
    return 0;
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

int linearRehash(cell* table[2], short alt, unsigned int size, char key[151], int data){
    
    unsigned int oldSize, i;
    
    for(i = 0; i < size; i++){
        table[alt][i].filled = False;
    }
    
    oldSize = size / expansionFactor;
    
    for(i = 0; i < oldSize; i++){
        if(table[!alt][i].filled){
            linearInsert(table[alt], size, table[!alt][i].key, table[!alt][i].data);
            //printf("OK: %d\n", i);
        }
    }
    
    //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
    if(linearInsert(table[alt], size, key, data)){
        return 1;
    }
    return 0;
}

int linkedInsert(linkedCell* table, unsigned int size, char key[151], int data){
    
    unsigned int index;
    node *test;
    node *temp;
    
    test = linkedSearch(table, &index, size, key);
    if(test == NULL){
        temp = table[index].first;
        test = (node*) malloc(sizeof(node));
        strcpy(test->key, key);
        test->data = data;
        table[index].first = test;
        table[index].first->next = temp;
        //test->next = temp;
        if(table[index].filled){
            return 0;
        }
        table[index].filled = True;
        return 1;
    }
    else{
        test->data = data;
        return 0;
    }
    return 0;
}

node * linkedSearch(linkedCell* table, unsigned int * index, unsigned int size, char key[151]){
    
    node *test;
    
    *index = hashFunctionA(key, size);
    
    if(table[*index].filled){ //ocupada
        test = table[*index].first;
        while(1){
            if(test == NULL){
                //return -1;
                return NULL;
            }
            else{
                if(!strcmp(test->key, key)){
                    //return test->data;
                    return test;
                }
                test = test->next;
            }
        }
    }
    else{
        //return -1;
        return NULL;
    }
    //return -1;
    return NULL;
}

int linkedRehash(linkedCell* table[2], short alt, unsigned int size, char key[151], int data){
    
    unsigned int oldSize, i;
    node *temp;
    
    for(i = 0; i < size; i++){
        table[alt][i].filled = False;
    }
    
    oldSize = size / expansionFactor;
    
    for(i = 0; i < oldSize; i++){
        if(table[!alt][i].filled){
            temp = table[!alt][i].first;
            while(temp != NULL){
                linkedInsert(table[alt], size, table[!alt][i].first->key, table[!alt][i].first->data);
                //printf("OK: %d\n", i);
                temp = temp->next;
                free(table[!alt][i].first);
                table[!alt][i].first = table[!alt][i].first->next;
            }
        }
    }
    
    //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
    if(linkedInsert(table[alt], size, key, data)){
        return 1;
    }
    return 0;
}