/* 
 * File:   hash.c
 * Author: Rodrigo Oliveira
 *
 * Created on 17 de Dezembro de 2013, 10:13
 */

#include "hash.h"
#include <sys/time.h>

int main(void) {
    
    char key[151], temp;
    int data;
    unsigned int size, maxSize, i, t;
    float trigger;
    
    maxSize = initialSize; //vai aumentar quando fizer rehashing (disparado pelo fator de carga limite)
    trigger = loadFactor * maxSize;
    size = 0;
    cell *table = (cell*) malloc(maxSize * sizeof(cell));
    
    double ti, tf, tempo; // ti = tempo inicial // tf = tempo final
    struct timeval tempo_inicio, tempo_fim;
    
    for(i = 0; i < maxSize; i++){
        table[i].filled = 0;
    }
    
    t = 1;
    while(1){
        
        if(t == 1){
            ti = 0;
            tf = 0;
            tempo = 0;
            gettimeofday(&tempo_inicio, NULL);
        }
        
        /*printf("\n|");
        for(i = 0; i < maxSize; i++){
            printf(" %d |", table[i].filled);
        }
        printf("\n\n\n\n\n\n\n");*/
        
        scanf("%s", key);
        
        temp = getchar();
        if(temp == ' '){
            scanf("%d", &data);
            if(size+1 > trigger){
                printf("Rehashing...\n");
                maxSize = maxSize * expansionFactor;
                trigger = loadFactor * maxSize;
                table = (cell*) realloc(table, maxSize * sizeof(cell));
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
                printf("[%d]\n", search(table, maxSize, key));
                //printf("%d\n", hashTable(SEARCH, key, 0));
            }
            else{
                printf("[FIM]\n");
                break;
            }
        }
        
        if(t == 100){
            t = 0;
            gettimeofday(&tempo_fim,NULL);
            tf = (double)tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (1000000.0));
            ti = (double)tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (1000000.0));
            tempo = (tf - ti) / 1000000.0;
            printf(" ::: Tempo: %lf\n", tempo);
        }
        t++;
        
    }
    return (EXIT_SUCCESS);
}
