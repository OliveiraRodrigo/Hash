#include "hash.h"
#include <string.h>

int linkedInsert(linkedCell* table, unsigned int size, char key[151], int data, unsigned int * retSize){
    
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
            //return 1;
        }
        table[index].filled = True;
        *retSize = *retSize + 1;
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
    
    *index = hashFunction(key, size);
    
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

int linkedRehash(linkedCell* table[2], short alt, unsigned int size, char key[151], int data, unsigned int * retSize){
    
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
                linkedInsert(table[alt], size, table[!alt][i].first->key, table[!alt][i].first->data, retSize);
                //printf("OK: %d\n", i);
                temp = temp->next;
                free(table[!alt][i].first);
                table[!alt][i].first = table[!alt][i].first->next;
            }
        }
    }
    
    //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
    if(linkedInsert(table[alt], size, key, data, retSize)){
        return 1;
    }
    return 0;
}
