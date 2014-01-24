#ifndef HASH_H

#define	HASH_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* HASH_H */

#include <stdio.h>
#include <stdlib.h>

#define string char*

#define False 0
#define True  1

/* Table */
#define initialSize 100
#define expansionFactor 2
#define loadFactor 0.43 // 0.0 <= x <= 1.0

/* Timer */
#define OFF   0
#define ON    1
#define START 0
#define GET   1
#define STOP  2

typedef struct{
    unsigned int size;
    unsigned int maxSize;
    float trigger;
    char alt;
} tableControl;

typedef struct{
    char key[151];
    int data;
    char filled; //ocupada
} cell;

typedef struct node{
    char key[151];
    int data;
    struct node * next;
} node;

typedef struct{
    char filled; //ocupada
    node * first;
} linkedCell;

/* Dois temporizadores: n == 0 ou 1
 * mark == START, GET ou STOP */
double timer(char n, char mark);

/* Funcao Hash proposta pelo professor */
unsigned int hashFunctionA(string key, unsigned int maxSize);

/* Funcao Hash buscada de outra fonte */
unsigned int hashFunction(string key, unsigned int maxSize);

/* Insere na lista com tratamento de colisao por busca linear */
int linearInsert(cell* table, unsigned int maxSize, string key, int data);

/* Busca na lista com tratamento de colisao por busca linear */
int linearSearch(cell* table, unsigned int maxSize, string key);

/* Rehash a lista com tratamento de colisao por busca linear */
int linearRehash(cell* table[2], short alt, unsigned int maxSize, string key, int data);

/* Visualizacao tosca da lista ... linear, melhor para tabelas pequenas */
void displayLinear(cell *table, unsigned int maxSize);

/* Insere na lista com tratamento de colisao por encadeamento */
char linkedInsert(linkedCell* table, unsigned int maxSize, string key, int data, unsigned int * size);

/* Busca na lista com tratamento de colisao por encadeamento */
int linkedSearch(linkedCell* table, unsigned int maxSize, string key);

/* Rehash a lista com tratamento de colisao por encadeamento */
char linkedRehash(linkedCell* table[2], short alt, unsigned int maxSize, string key, int data, unsigned int * size);

/* Visualizacao tosca da lista ... encadeamento */
void displayLinked(linkedCell *table, unsigned int maxSize);
