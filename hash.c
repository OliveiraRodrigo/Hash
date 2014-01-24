#include "hash.h"
#include <sys/time.h>

int main(void){
    
    //cell *table[2];
    linkedCell *table[2];
    tableControl ctrl;
    string key;
    int data;
    char temp;
    int i, t;
    
    //Inicializa os controles e aloca memoria para a tabela principal.
    #define size    ctrl.size
    #define maxSize ctrl.maxSize
    #define trigger ctrl.trigger
    #define alt     ctrl.alt
    maxSize = initialSize; //Vai aumentar quando fizer rehash (disparado pela carga limite + 1).
    trigger = (float) (1 + maxSize * loadFactor);
    size = 0;
    alt = 0; //Alterna entre as 2 tabelas, a partir de um rehash.
    //table[.alt] = (cell*) malloc(.maxSize * sizeof(cell));
    table[alt] = (linkedCell*) malloc(maxSize * sizeof(linkedCell));
    key = (string) malloc(151 * sizeof(char));
    
    //Zera a flag 'filled' e seta o ponteiro 'first' de toda a tabela.
    for(i = 0; i < maxSize; i++){
        table[alt][i].filled = False;
        table[alt][i].first = NULL;
    }
    
    printf("\r\n-----------------------------------------------\r\n");
    printf("REHASH   |   SIZE  |  TIME (ms)  | RH TIME (ms)");
    printf("\r\n-----------------------------------------------\r\n\r\n");
    
    t = 1; //Em 1000, mostra o tempo e reinicia o timer 0.
    i = 0; //Um contador so pra ajudar nuns printf.
    
    while(1){
        
        if(t == 1){
            //Inicia o timer 0.
            timer(0, START);
        }
        
        //displayLinear(table[alt], maxSize);
        //displayLinked(table[alt], maxSize);
        //printf("Size:[%u]\r\n", size);
        //printf("Trig:[%f]\r\n", trigger);
        
        //Pega a chave.
        scanf("%s", key);
        
        //Pega o separador: espaco, tab ou enter?
        temp = getchar();
        
        if(temp == ' ' || temp == '\t'){
            
            //Era 'espaco' ou 'tab', entao pega o dado.
            scanf("%d", &data);
            
            //Se o tamanho da tabela for ultrapassar o limite: Rehash it!
            if(size+1 >= trigger){
                
                printf("Rehashing ");
                //printf("\r\n");
                timer(1, START);
                alt = !alt; //Alterna as tabelas. Agora a nova sera a principal.
                maxSize *= expansionFactor; //Expande a tabela nova.
                trigger = (float) (1 + maxSize * loadFactor); //Atualiza o gatilho.
                //Partiu REHASH!
                
                //Aloca memoria para a tabela nova.
                /*table[alt] = (cell*) malloc(maxSize * sizeof(cell));
                if(linearRehash(table, alt, maxSize, key, data)){
                    size++;
                }
                else{
                    
                }*/
                
                //Aloca memoria para a tabela nova.
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
                
                //Desaloca a tabela antiga.
                free(table[!alt]);
                //printf("Fim Rehashing ");
                //printf("\r\n");
            }
            //Se o tamanho da tabela NAO for ultrapassar o limite: Insere.
            else{
                //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
                //printf("'%s'\r\n", key);
                //if(linearInsert(table[alt], maxSize, key, data)){
                if(linkedInsert(table[alt], maxSize, key, data, &size)){
                    //Inseriu sem colisao.
                    //size++; //So se for a linear, para atualizar o tamanho aqui.
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
            //Era 'enter', entao busca a chave.
            if(temp == 13 || temp == 10){
                //printf("Buscar: Key: '%s': ", key);
                //printf("[%d]\n", linearSearch(table[alt], maxSize, key));
                printf("%d\r\n", linkedSearch(table[alt], maxSize, key));
            }
            //E' o fim do arquivo.
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
