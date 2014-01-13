/* 
 * File:   hash.c
 * Author: Rodrigo Oliveira
 *
 * Created on 17 de Dezembro de 2013, 10:13
 */

#include "hash.h"

int main(void) {
    
    char key[200], temp;
    unsigned int data, size, maxSize, i;
    float loadFactor, trigger, expansionFactor;
    
    loadFactor = 1/*0.7*/;
    expansionFactor = 2;
    maxSize = 100; //vai aumentar quando fizer rehashing (disparado pelo fator de carga limite)
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
            if(size+1 > trigger){
                maxSize = maxSize * expansionFactor;
                //rehash(table, maxSize, key, data);
            }
            else{
                printf("Inserir:\nKey: '%s' ::: Data: '%u'\n", key, data);
                size += insert(table, maxSize, key, data);
                //printf("\nsize: '%u'\n", size);
                printf("0\n");// 0(zero) means: OK.
            }
        }
        else{
            if(temp == 13 || temp == 10){ //ENTER
                printf("Buscar:\nKey: '%s'\n", key);
                printf("%d\n", search(table, maxSize, key));
            }
            else{
                printf("[FIM]\n");
                break;
            }
        }
    }
    return (EXIT_SUCCESS);
}
