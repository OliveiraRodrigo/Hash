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
    cell *table = malloc(maxSize*sizeof(cell));
    
    for(i = 0; i < maxSize; i++){
        table[i].filled = 0;
    }
    
    while(1){
        
        scanf("%s", key);
        
        temp = getchar();
        if(temp == ' '){
            scanf("%u", &data);
            if(size+1 >= trigger){
                maxSize = maxSize * expansionFactor;
                realloc(table, maxSize * sizeof(cell));
                //rehash(table, maxSize, key, data);
                /*for(i = 0; i < maxSize; i++){
                    printf("%d: [%d]\n", i, table[i].data);
                }*/
            }
            else{
                //printf("Inserir:\nKey: '%s' ::: Data: '%d'\n", key, data);
                if(insert(table, maxSize, key, data) == 0){
                    size++;
                    printf("0\n");
                }
                else{
                    printf("-1\n");
                }
                //printf("\n");
                printf("\nsize: '%u'\n", size);
                //printf("%d\n", hashTable(INSERT, key, data));// 0(zero) means: OK.
            }
        }
        else{
            if(temp == 13 || temp == 10){ //ENTER
                //printf("Buscar:\nKey: '%s'\n", key);
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
