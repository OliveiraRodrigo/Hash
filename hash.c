#include "hash.h"
#include <sys/time.h>

int main(void) {
    
    char key[151], temp;
    int data;
    unsigned int size, maxSize, index, i, t;
    float trigger;
    short alt;
    
    maxSize = initialSize; //vai aumentar quando fizer rehashing (disparado pelo fator de carga limite)
    trigger = 1 + maxSize * loadFactor;
    size = 0;
    alt = 0; //alterna entre as 2 tabelas, a partir de um rehash
    //cell *table[2];
    linkedCell *table[2];
    node * test;
    //table[alt] = (cell*) malloc(maxSize * sizeof(cell));
    table[alt] = (linkedCell*) malloc(maxSize * sizeof(linkedCell));
    
    for(i = 0; i < maxSize; i++){
        table[alt][i].filled = False;
        table[alt][i].first = NULL;
        table[alt][i].last = NULL;
    }
    
    printf("\r\n-----------------------------------------------\r\n");
    printf("REHASH   |   SIZE  |  TIME (ms)  | RH TIME (ms)");
    printf("\r\n-----------------------------------------------\r\n\r\n");
    t = 1;
    while(1){
        //printf("t[%d]", t);
        if(t == 1){
            timer(0, START);
        }
        
        /*printf("\n|");
        for(i = 0; i < maxSize; i++){
            if(table[alt][i].filled)
                printf(" %d |", table[alt][i].filled);
            else
                printf("   |");
        }
        printf("\n|");
        for(i = 0; i < maxSize; i++){
            if(table[alt][i].filled){
                if(table[alt][i].first->next != NULL){
                    printf(" * |");
                }
                else
                    printf("   |");
            }
            else
                printf("   |");
        }
        printf("\n\n\n\n\n\n\n");*/
        display(table[alt], maxSize);
        printf("Size:[%u]\r\n", size);
        printf("Trig:[%f]\r\n", trigger);
        
        scanf("%s", key);
        
        temp = getchar();
        if(temp == ' '){
            scanf("%d", &data);
            if(size+1 >= trigger){
                printf("Rehashing ");
                //exit(0);
                timer(1, START);
                alt = !alt;
                maxSize = maxSize * expansionFactor;
                trigger = 1 + maxSize * loadFactor;
                /*table[alt] = (cell*) malloc(maxSize * sizeof(cell));
                if(linearRehash(table, alt, maxSize, key, data)){
                    size++;
                }
                else{
                    
                }*/
                table[alt] = (linkedCell*) malloc(maxSize * sizeof(linkedCell));
                size = 0;
                if(linkedRehash(table, alt, maxSize, key, data, &size)){
                    
                }
                else{
                    
                }
                //printf("0\r\n");
                printf("[%07u]", size);
                printf(" %26.3lf\r\n", timer(1, STOP));
                free(table[!alt]);
            }
            else{
                //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
                //if(linearInsert(table[alt], maxSize, key, data)){
                if(linkedInsert(table[alt], maxSize, key, data, &size)){
                    //size++;
                }
                else{
                    
                }
                //printf("0\r\n");
                //printf(" size[%u]\r\n", size);
            }
        }
        else{
            if(temp == 13 || temp == 10){ //ENTER
                //printf("Buscar: Key: '%s': ", key);
                //printf("[%d]\n", linearSearch(table[alt], maxSize, key));
                test = (node*) malloc(sizeof(node));
                test = linkedSearch(table[alt], &index, maxSize, key);
                if(test){
                    printf("[%d]\r\n", test->data);
                }
                else{
                    printf("[-1]\n");
                }
            }
            else{
                printf("          [%07u]\r\n", size);
                printf("[FIM]\r\n");
                break;
            }
        }
        
        if(t == 1000){
            t = 0;
            printf("          [%07u]", size);
            printf(" %12.3lf\r\n", timer(0, STOP));
        }
        t++;
    }
    //display(table[alt], maxSize);
    return (EXIT_SUCCESS);
}

double timer(short n, short mark){
    
    static short state[2] = {OFF, OFF};
    static double tIn[2] = {0.0, 0.0};
    double tOut, time;
    struct timeval getTime;
    
    switch(mark){
        
        case START:
            gettimeofday(&getTime, NULL);
            tIn[n] = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            state[n] = ON;
            return 0.0;
            break;
        
        case GET:
            if(state[n] == OFF){
                return 0.0;
            }
            gettimeofday(&getTime, NULL);
            tOut = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            time = (tOut - tIn[n]) / 1000.0;
            return time;
            break;
    
        case STOP:
            if(state[n] == OFF){
                return 0.0;
            }
            gettimeofday(&getTime, NULL);
            tOut = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            time = (tOut - tIn[n]) / 1000.0;
            state[n] = OFF;
            return time;
            break;
    }
}

void display(linkedCell *table, unsigned int size){
    
    unsigned int i;
    node* temp;
    
    for(i = 0; i < size; i++){
        printf("[%u]", i);
        temp = table[i].first;
        while(temp != NULL){
            printf("->[ * ]");
            temp = temp->next;
        }
        printf("\r\n");
    }
}
