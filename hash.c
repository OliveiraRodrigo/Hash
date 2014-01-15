/* 
 * File:   hash.c
 * Author: Rodrigo Oliveira
 *
 * Created on 17 de Dezembro de 2013, 10:13
 */

#include "hash.h"

int main(void) {
    
    char key[151], temp;
    int data;
    unsigned int size, maxSize, i;
    float trigger;
    
    maxSize = initialSize; //vai aumentar quando fizer rehashing (disparado pelo fator de carga limite)
    trigger = loadFactor * maxSize;
    size = 0;
    cell *table = malloc(maxSize * sizeof(cell));
    cell *tempPtr;
    
    for(i = 0; i < maxSize; i++){
        table[i].filled = 0;
    }
    
    while(1){
        
        printf("\n|");
        for(i = 0; i < maxSize; i++){
            printf(" %d |", table[i].filled);
        }
        printf("\n\n\n\n\n\n\n");
        
        scanf("%s", key);
        
        temp = getchar();
        if(temp == ' '){
            scanf("%d", &data);
            if(size+1 > trigger){
                printf("Rehashing...\n");
                tempPtr = table;
                table += maxSize * sizeof(cell);
                maxSize = maxSize * expansionFactor;
                table = malloc((maxSize/expansionFactor) * sizeof(cell));
                table = tempPtr;
                
                /*printf("Reallocated\n|");
                for(i = 0; i < maxSize; i++){
                    printf(" %d |", table[i].filled);
                }
                printf("\n\n\n\n\n\n\n");*/
                
                trigger = loadFactor * maxSize;
                //realloc(table, maxSize * sizeof(cell));
                if(rehash(table, maxSize, key, data) == 0){
                    size++;
                    printf(" size[%d]\n", size);
                    //printf("0\n");
                }
                else{
                    //printf("-1\n");
                }
            }
            else{
                printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
                if(insert(table, maxSize, key, data) == 0){
                    size++;
                    printf(" size[%d]\n", size);
                    //printf("0\n");
                }
                else{
                    //printf("-1\n");
                }
                //printf("\n");
                //printf("\nsize: '%u'\n", size);
                //printf("%d\n", hashTable(INSERT, key, data));// 0(zero) means: OK.
            }
        }
        else{
            if(temp == 13 || temp == 10){ //ENTER
                printf("Buscar: Key: '%s': ", key);
                printf("%d\n", search(table, maxSize, key));
                //printf("%d\n", hashTable(SEARCH, key, 0));
            }
            else{
                printf("[FIM]\n");
                break;
            }
        }
    }
    return (EXIT_SUCCESS);
}
