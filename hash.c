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
    
    double ti, tf, time; // ti = tempo inicial // tf = tempo final
    struct timeval timeIn, timeOut, rehashTimeIn, rehashTimeOut;
    
    for(i = 0; i < maxSize; i++){
        table[i].filled = 0;
    }
    
    printf("\r\n-----------------------------------------------\r\n");
    printf("REHASH   |   SIZE  |  TIME (ms)  | RH TIME (ms)");
    printf("\r\n-----------------------------------------------\r\n\r\n");
    t = 1;
    while(1){
        
        if(t == 1){
            gettimeofday(&timeIn, NULL);
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
                printf("Rehashing ");
                gettimeofday(&rehashTimeIn, NULL);
                maxSize = maxSize * expansionFactor;
                trigger = loadFactor * maxSize;
                table = (cell*) realloc(table, maxSize * sizeof(cell));
                if(rehash(table, maxSize, key, data) == 0){
                    size++;
                    printf("[%07d]", size);
                    //printf("0\n");
                    gettimeofday(&rehashTimeOut, NULL);
                    tf = (double)rehashTimeOut.tv_usec + ((double)rehashTimeOut.tv_sec * (1000000.0));
                    ti = (double)rehashTimeIn.tv_usec + ((double)rehashTimeIn.tv_sec * (1000000.0));
                    time = (tf - ti) / 1000.0;
                    printf(" %26.3lf\r\n", time);
                }
                else{
                    //printf("-1\n");
                }
            }
            else{
                //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
                if(insert(table, maxSize, key, data) == 0){
                    size++;
                    //printf("[%d]\r\n", size);
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
                //printf("Buscar: Key: '%s': ", key);
                //printf("[%d]\n", search(table, maxSize, key));
            }
            else{
                printf("          [%07d]\r\n", size);
                printf("[FIM]\n");
                break;
            }
        }
        
        if(t == 1000){
            t = 0;
            gettimeofday(&timeOut, NULL);
            tf = (double)timeOut.tv_usec + ((double)timeOut.tv_sec * (1000000.0));
            ti = (double)timeIn.tv_usec + ((double)timeIn.tv_sec * (1000000.0));
            time = (tf - ti) / 1000.0;
            printf("          [%07d]", size);
            printf(" %12.3lf\r\n", time);
        }
        t++;
        
    }
    return (EXIT_SUCCESS);
}
