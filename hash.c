#include "hash.h"
#include <sys/time.h>

#define size            ctrl.size
#define maxSize         ctrl.maxSize
#define trigger         ctrl.trigger
#define alt             ctrl.alt

int main(void){
    
    timer(0, START); //Tempo total de execucao
    
    //cell *table[2];
    linkedCell *table[2];
    tableControl ctrl;
    string key;
    int data;
    char temp;
    int i, ins, search;
    double totInsTime = 0, totSrchTime = 0;
    
    //Inicializa os controles e aloca memoria para a tabela principal.
    maxSize = initialSize; //Vai aumentar quando fizer rehash (disparado pela carga limite + 1).
    trigger = (float) (1 + maxSize * loadFactor);
    size    = 0;
    alt     = 0; //Alterna entre as 2 tabelas, a partir de um rehash.
    
    //table[alt] = (cell*)       malloc(maxSize * sizeof(cell));
    table[alt] = (linkedCell*) malloc(maxSize * sizeof(linkedCell));
    key        = (string)      malloc(151     * sizeof(char));
    
    //Zera a flag 'filled' e seta o ponteiro 'first' de toda a tabela.
    for(i = 0; i < maxSize; i++){
        table[alt][i].filled = False;
        table[alt][i].first = NULL; //So para a linkedCell.
    }
    
    printf("Initial Size:     %29d\r\n",   initialSize);
    printf("Expansion Factor: %29d\r\n",   expansionFactor);
    printf("Load Factor:      %29.2f\r\n", loadFactor);
    
    printf("\r\n-----------------------------------------------\r\n");
    printf("REHASH   |   SIZE  |  TIME (ms)  | RH TIME (ms)");
    printf("\r\n-----------------------------------------------\r\n\r\n");
    
    ins    = 1; //Em 1000 insercoes, mostra o tempo e reinicia o timer 1.
    search = 1; //Em 1000 buscas,    mostra o tempo e reinicia o timer 2.
    i      = 0; //Um contador para testes bizarros nao autorizados em humanos.
    
    while(1){
        
        //displayLinear(table[alt], maxSize);
        //displayLinked(table[alt], maxSize);
        
        //Pega a chave.
        scanf("%s", key);
        
        //Pega o separador: espaco, tab ou enter?
        temp = getchar();
        
        if(temp == ' ' || temp == '\t'){
            
            //Era 'espaco' ou 'tab', entao pega o dado.
            scanf("%d", &data);
            
            timer(1, START); //1000 insercoes
            timer(2, PAUSE); //1000 buscas
            
            //Se o tamanho da tabela for ultrapassar o limite: Rehash it!
            if(size+1 >= trigger){
                
                printf("Rehashing ");
                timer(3, START);            //Rehash individual
                alt = !alt;                 //Alterna as tabelas: agora a nova sera a principal.
                maxSize *= expansionFactor; //Novo tamanho para expandir a tabela nova.
                trigger = (float) (1 + maxSize * loadFactor); //Atualiza o gatilho.
                //Partiu REHASH!
                
                //Aloca memoria para a tabela nova.
                /*table[alt] = (cell*) malloc(maxSize * sizeof(cell));
                if(linearRehash(table, alt, maxSize, key, data)){
                    //Inseriu nova chave.
                    size++;
                }
                else{
                    //Reinseriu chave que ja tinha.
                }*/
                table[alt] = (linkedCell*) malloc(maxSize * sizeof(linkedCell));
                if(linkedRehash(table, alt, maxSize, key, data, &size)){
                    //Inseriu sem colisao.
                }
                else{
                    //Inseriu com colisao.
                }
                //printf("0\r\n");
                printf("[%07u]", size);
                printf(" %26.3lf\r\n", timer(3, STOP));
                
                //Desaloca a tabela antiga.
                free(table[!alt]);
            }
            //Se o tamanho da tabela NAO for ultrapassar o limite: Insere.
            else{
                //if(linearInsert(table[alt], maxSize, key, data)){
                
                if(linkedInsert(table[alt], maxSize, key, data, &size)){
                    //Inseriu sem colisao.
                    //size++; //So se for a linear, para atualizar o tamanho aqui.
                }
                else{
                    //Inseriu com colisao.
                }
                //printf("0\r\n");
                
                //Mostra o tempo de 1000 insercoes e para o timer 1.
                if(ins == 1000){
                    ins = 0;
                    printf("          [%07u]", size);
                    printf(" %12.3lf\r\n", timer(1, GET));
                    totInsTime += timer(1, STOP);
                }
                ins++;
            }
        }
        else{
            //Era 'enter', entao busca a chave.
            if(temp == 13 || temp == 10){
                
                timer(1, PAUSE); //1000 insercoes
                timer(2, START); //1000 buscas
                
                //data = linearSearch(table[alt], maxSize, key);
                data = linkedSearch(table[alt], maxSize, key);
                //printf("%4d\r\n", data);
                
                //Mostra o tempo de 1000 buscas e para o timer 2.
                if(search == 1000){
                    search = 0;
                    printf("%4d", data);
                    printf("%28.3lf\r\n", timer(2, GET));
                    totSrchTime += timer(2, STOP);
                }
                search++;
            }
            //E' o fim do arquivo.
            else{
                printf("          [%07u]\r\n", size);
                printf("[FIM]\r\n");
                break;
            }
        }
    }
    printf("\r\nTotal insertions time: %20.3lf ms\r\n",  totInsTime + timer(1, STOP));
    printf("Total searches time: %22.3lf ms\r\n"      , totSrchTime + timer(2, STOP));
    printf("Total execution time: %21.3lf ms\r\n"     ,               timer(0, STOP));
    //displayLinked(table[alt], maxSize);
    return (EXIT_SUCCESS);
}

double timer(char n, char mark){
    
    static bool  state[4] = {OFF, OFF, OFF, OFF};
    static double time[4] = {0.0, 0.0, 0.0, 0.0};
    static double  tIn[4];
    double tOut;
    struct timeval getTime;
    
    switch(mark){
        
        case START:
            if(state[n] == ON){
                return time[n];
            }
            if(state[n] == OFF){
                time[n] = 0.0;
            }
            state[n] = ON;
            gettimeofday(&getTime, NULL);
            tIn[n] = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            return time[n];
            break;
        
        case GET:
            if(state[n] == OFF){
                return 0.0;
            }
            if(state[n] == PAUSE){
                return time[n];
            }
            gettimeofday(&getTime, NULL);
            tOut = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            return (tOut - tIn[n]) / 1000.0;
            break;
            
        case PAUSE:
            if(state[n] == OFF){
                return 0.0;
            }
            if(state[n] == PAUSE){
                return time[n];
            }
            state[n] = PAUSE;
            gettimeofday(&getTime, NULL);
            tOut = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            time[n] += (tOut - tIn[n]) / 1000.0;
            return time[n];
            break;
            
        case STOP:
            if(state[n] == OFF){
                return 0.0;
            }
            if(state[n] == PAUSE){
                state[n] = OFF;
                return time[n];
            }
            gettimeofday(&getTime, NULL);
            tOut = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            time[n] += (tOut - tIn[n]) / 1000.0;
            state[n] = OFF;
            return time[n];
            break;
    }
}
