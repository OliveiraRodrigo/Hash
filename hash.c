#include "hash.h"
#include <sys/time.h>

int main(void){
    
    char key[151], temp;
    int data;
    unsigned int size, maxSize, i, t;
    float trigger;
    char alt;
    //cell *table[2];
    linkedCell *table[2];
    
    //Inicializa os controles e aloca a tabela principal
    maxSize = initialSize; //vai aumentar quando fizer rehashing (disparado pelo fator de carga limite)
    trigger = (float) (1 + maxSize * loadFactor);
    size = 0;
    alt = 0; //Alterna entre as 2 tabelas, a partir de um rehash.
    //table[alt] = (cell*) malloc(maxSize * sizeof(cell));
    table[alt] = (linkedCell*) malloc(maxSize * sizeof(linkedCell));
    
    //Zera a flag 'filled' e seta o ponteiro 'first' de toda a tabela.
    for(i = 0; i < maxSize; i++){
        table[alt][i].filled = False;
        table[alt][i].first = NULL;
    }
    
    printf("\r\n-----------------------------------------------\r\n");
    printf("REHASH   |   SIZE  |  TIME (ms)  | RH TIME (ms)");
    printf("\r\n-----------------------------------------------\r\n\r\n");
    
    t = 1; //Em 1000, mostra o tempo e reinicia o timer 0.
    i = 0;
    while(1){
        if(t == 1){
            //Inicia o timer 0.
            timer(0, START);
        }
        
        // Apenas para visualizacao
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
        //display(table[alt], maxSize);
        //printf("Size:[%u]\r\n", size);
        //printf("Trig:[%f]\r\n", trigger);
        
        scanf("%s", key); //Pega a chave.
        
        temp = getchar(); //Pega o separador: espaco, tab ou enter?
        if(temp == ' ' || temp == '\t'){
            scanf("%d", &data); //Era 'espaco', entao pega o dado.
            if(size+1 >= trigger){ //O tamanho da tabela ultrapassaria o limite.
                printf("Rehashing ");
                //printf("\r\n");
                timer(1, START);
                alt = !alt; //Alterna as tabelas. Agora a principal sera a nova.
                maxSize = maxSize * (int) expansionFactor; //Expande a tabela nova.
                trigger = (float) (1 + maxSize * loadFactor); //Atualiza o gatilho.
                //Partiu REHASH!
                /*table[alt] = (cell*) malloc(maxSize * sizeof(cell));
                if(linearRehash(table, alt, maxSize, key, data)){
                    size++;
                }
                else{
                    
                }*/
                table[alt] = (linkedCell*) malloc(maxSize * sizeof(linkedCell));
                if(linkedRehash(table, alt, maxSize, key, data, &size)){
                    //printf("[%u]\r\n", i++);
                }
                else{
                    //printf("[%u] col\r\n", i++);
                }
                //printf("0\r\n");
                printf("[%07u]", size);
                printf(" %26.3lf\r\n", timer(1, STOP));
                free(table[!alt]); //Desaloca a tabela antiga.
                //printf("Fim Rehashing ");
                //printf("\r\n");
            }
            else{
                //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
                //printf("'%s'\r\n", key);
                //if(linearInsert(table[alt], maxSize, key, data)){
                if(linkedInsert(table[alt], maxSize, key, data, &size)){
                    //Inseriu sem colisao.
                    //size++;
                    //printf("[%u / %u]\r\n", i++, maxSize);
                }
                else{
                    //Inseriu com colisao.
                    //printf("[%u] col\r\n", i++);
                }
                //printf("0\r\n");
                //printf(" size[%u]\r\n", size);
                //printf("maxSize:[%u]\r\n", maxSize);
            }
        }
        else{
            if(temp == 13 || temp == 10){ //Era 'enter', entao busca a chave.
                printf("Buscar: Key: '%s': ", key);
                //printf("[%d]\n", linearSearch(table[alt], maxSize, key));
                printf("%d\r\n", linkedSearch(table[alt], /*&index,*/ maxSize, key));
            }
            else{
                printf("          [%07u]\r\n", size);
                printf("[FIM]\r\n");
                break;
            }
        }
        
        //Mostra o tempo de 1000 insercoes e para o timer 0.
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

double timer(char n, char mark){
    
    static char state[2] = {OFF, OFF};
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
