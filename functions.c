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
            table[index].filled = 1;
            return 0;
        }
    }
    while(start != index);
    
    return -1;
}
/*
int linkedInsert(linkedCell* table, unsigned int size, char key[151], int data){
    
    unsigned int index;
    node *test;
    //node *temp;
    
    index = hashFunctionA(key, size);
    
    if(table[index].filled){ //ocupada
        //test = (node*) malloc (sizeof(node));
        test = table[index].first;
        //temp = table[index].first;
        
        while(1){
            if(test == NULL){
            //if(table[index].first == NULL){
                //test = (node*) malloc (sizeof(node));
                strcpy(test->key, key);
                test->data = data;
                test->next = (node*) malloc (sizeof(node));
                test->next = NULL;
                
                /*table[index].first = (node*) malloc (sizeof(node));
                strcpy(table[index].first->key, key);
                table[index].first->data = data;
                table[index].first->next = (node*) malloc (sizeof(node));
                table[index].first->next = NULL;
                table[index].first = temp;*//*
                return 0;
                break;
            }
            else{
                if(!strcmp(test->key, key)){
                    test->data = data;
                /*if(!strcmp(table[index].first->key, key)){
                    table[index].first->data = data;
                    table[index].first = temp;*//*
                    return 0;
                }
                test = test->next;
                //table[index].first = table[index].first->next;
            }
        }
    }
    else{
        table[index].filled = 1;
        table[index].first = (node*) malloc(sizeof(node));
        strcpy(table[index].first->key, key);
        table[index].first->data = data;
        table[index].first->next = (node*) malloc(sizeof(node));
        table[index].first->next = NULL;
        return 0;
    }
    return -1;
}
*/
int linkedInsert(linkedCell* table, unsigned int size, char key[151], int data){
    
    unsigned int index;
    int p = 0;
    //node *test;
    node *temp;
    
    //test = linkedSearch(table, size, key);
    //if(test == NULL)
    
    index = hashFunctionA(key, size);
    
    if(table[index].filled){ //ocupada
        //test = (node*) malloc (sizeof(node));
        //test = table[index].first;
        //temp = table[index].first;
        
        while(1){
            //if(test == NULL){
            if(table[index].first == NULL){
                printf("\nffffff\n");
                /*test = (node*) malloc (sizeof(node));
                strcpy(test->key, key);
                test->data = data;
                test->next = (node*) malloc (sizeof(node));
                test->next = NULL;*/
                
                table[index].first = (node*) malloc (sizeof(node));
                strcpy(table[index].first->key, key);
                table[index].first->data = data;
                table[index].first->next = (node*) malloc (sizeof(node));
                table[index].first->next = NULL;
                //table[index].first = temp;
                
                while(p > 0){
                    temp = table[index].first;
                    table[index].first = table[index].first->prev;
                    table[index].first->next = temp;
                    p--;
                }
                
                return 0;
                break;
            }
            else{
                /*if(!strcmp(test->key, key)){
                    test->data = data;*/
                if(!strcmp(table[index].first->key, key)){
                    table[index].first->data = data;
                    //table[index].first = temp;
                    return 0;
                }
                //test = test->next;
                                printf("\nf1\n");
                temp = table[index].first;
                                printf("\nf2\n");
                table[index].first = table[index].first->next;
                                printf("\nf3\n");
                //table[index].first->prev = (node*) malloc(sizeof(node));
                                printf("\nf3.5\n");
                table[index].first->prev = temp;
                                printf("\nf4\n");
                p++;
            }
        }
    }
    else{
        table[index].filled = 1;
        table[index].first = (node*) malloc(sizeof(node));
        strcpy(table[index].first->key, key);
        table[index].first->data = data;
        table[index].first->prev = (node*) malloc(sizeof(node));
        table[index].first->next = (node*) malloc(sizeof(node));
        table[index].first->prev = NULL;
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

/*int*/ node * linkedSearch(linkedCell* table, unsigned int size, char key[151]){
    
    unsigned int index;
    node *test;
    
    index = hashFunctionA(key, size);
    
    if(table[index].filled){ //ocupada
        //test = (node*) malloc (sizeof(node));
        test = table[index].first;
        while(1){
            if(test == NULL){
            //if(table[index].first == NULL){
                //free(test);
                printf("\nopa\n");
                //return -1;
                return NULL;
            }
            else{
                printf("\nqqq\n");
                if(!strcmp(test->key, key)){
                    //return test->data;
                    return test;
                }
                /*if(!strcmp(table[index].first->key, key)){
                    return table[index].first->data;
                }*/
                test = test->next;
                //test = (node*) malloc (sizeof(node));
                //table[index].first = table[index].first->next;
            }
        }
    }
    else{
        printf("\nXopaX\n");
        //return -1;
        return NULL;
    }
    printf("\nYopaY\n");
    //return -1;
    return NULL;
}
/*
int linearRehash(cell* table, unsigned int size, char key[151], int data){
    
    unsigned int oldSize, tempSize, i, j;
    cell *tempTable;
    
    oldSize = size / expansionFactor;
    j = 0;
    
    tempTable = (cell*) malloc(oldSize * sizeof(cell));
    for(i = 0; i < oldSize; i++){
        if(table[i].filled){
            strcpy(tempTable[j].key, table[i].key);
            tempTable[j].data = table[i].data;
            table[i].filled = 0;
            j++;
        }
    }
    tempSize = j;
    i = oldSize;
    while(i < size){
        table[i].filled = 0;
        //printf("%d\n", i);
        i++;
    }
    
    for(j = 0; j < tempSize; j++){
        if(linearInsert(table, size, tempTable[j].key, tempTable[j].data) == -1){
            //printf("Erro: %d\n", i);
            return -1;
        }
        else{
            //printf("OK: %d\n", i);
        }
    }
    free(tempTable);
    if(linearInsert(table, size, key, data) == 0){
        //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
        return 0;
    }
    
    return -1;
}
*/
int linearRehash(cell* table[2], short alt, unsigned int size, char key[151], int data){
    
    unsigned int oldSize, i;
    
    for(i = 0; i < size; i++){
        //reTable[i].filled = 0;
        table[alt][i].filled = 0;
    }
    
    oldSize = size / expansionFactor;
    
    for(i = 0; i < oldSize; i++){
        if(table[!alt][i].filled){
            if(linearInsert(table[alt], size, table[!alt][i].key, table[!alt][i].data) == -1){
                //printf("Erro: %d\n", i);
                return -1;
            }
            
            //table[i].filled = 0;
            //printf("OK: %d\n", i);
        }
    }
    
    if(linearInsert(table[alt], size, key, data) == -1){
        return -1;
    }
    //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
    //table = reTable;
    return 0;
}
