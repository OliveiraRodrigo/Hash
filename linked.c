#include "hash.h"
#include <string.h>

char linkedInsert(linkedCell* table, unsigned int maxSize, string key, int data, unsigned int * size){
    
    unsigned int index;
    node *test;
    node *temp;
    
    index = DEKHash(key, maxSize);
    
    if(table[index].filled){
        temp = table[index].first;
        test = (node*) malloc(sizeof(node));
        strcpy(test->key, key);
        test->data = data;
        table[index].first = test;
        table[index].first->next = temp;
        //printf("[]%s\t%d\r\n", key, data);
        //Insercao com colisao: nao aumentou o tamanho da tabela.
        return False;
    }
    else{
        table[index].first = (node*) malloc(sizeof(node));
        strcpy(table[index].first->key, key);
        table[index].first->data = data;
        table[index].first->next = NULL;
        table[index].filled = True;
        *size = *size + 1;
        //printf("%s\t%d\r\n", key, data);
        //Insercao sem colisao: aumentou o tamanho da tabela.
        return True;
    }
    return False;
}

int linkedSearch(linkedCell* table, unsigned int maxSize, string key){
    
    node *test;
    unsigned int index;
    
    index = DEKHash(key, maxSize);
    
    if(table[index].filled){ //ocupada
        test = table[index].first;
        while(1){
            if(test == NULL){
                return -1;
            }
            else{
                if(!strcmp(test->key, key)){
                    return test->data;
                }
                test = test->next;
            }
        }
    }
    else{
        return -1;
    }
    return -1;
}

bool linkedRehash(linkedCell* table[2], bool alt, unsigned int maxSize, string key, int data, unsigned int * size){
    
    unsigned int oldSize, i, n;
    node *temp, **invert;
    
    for(i = 0; i < maxSize; i++){
        table[alt][i].filled = False;
    }
    
    oldSize = maxSize / expansionFactor;
    *size = 0;
    
    for(i = 0; i < oldSize; i++){
        if(table[!alt][i].filled){
            //Guarda todos numa lista temporaria, para inserir de tras pra frente
            n = 0;
            invert = (node**) malloc(sizeof(node*));
            while(table[!alt][i].first != NULL){
                invert = (node**) realloc(invert, (n+1)*sizeof(node*));
                invert[n] = (node*) malloc(sizeof(node));
                temp = table[!alt][i].first;
                strcpy(invert[n]->key, temp->key);
                invert[n]->data = temp->data;
                table[!alt][i].first = table[!alt][i].first->next;
                free(temp);
                n++;
            }
            while(n > 0){
                n--;
                linkedInsert(table[alt], maxSize, invert[n]->key, invert[n]->data, size);
                free(invert[n]);
                //printf("\r\n%s\r\n", temp->key);
            }
            free(invert);
        }
    }
    
    //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
    if(linkedInsert(table[alt], maxSize, key, data, size)){
        //printf("'%s'\r\n", key);
        return 1;
    }
    //printf("'%s'\r\n", key);
    return 0;
}

void displayLinked(linkedCell *table, unsigned int maxSize){
    
    unsigned int i;
    node* temp;
    
    for(i = 0; i < maxSize; i++){
        printf("[%u]", i);
        temp = table[i].first;
        while(temp != NULL){
            printf("->[ * ]");
            temp = temp->next;
        }
        printf("\r\n");
    }
}
