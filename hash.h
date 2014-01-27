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
#define bool char
#define False 0
#define True  1

/* Table */
#define initialSize     100
#define expansionFactor   2
#define loadFactor      0.18 // 0.0 <= x <= 1.0

/* Timer */
#define OFF   0
#define ON    1
#define START 0
#define GET   1
#define PAUSE 2
#define STOP  3

typedef struct{
    unsigned int size;
    unsigned int maxSize;
    float trigger;
    bool alt;
} tableControl;

typedef struct{
    char key[151];
    int data;
    bool filled; //ocupada
} cell;

typedef struct node{
    char key[151];
    int data;
    struct node * next;
} node;

typedef struct{
    bool filled; //ocupada
    node * first;
} linkedCell;

/* Quatro timers: n == [0 a 3]
 * mark == START, GET, PAUSE ou STOP */
double timer(char n, char mark);

/* Funcao Hash proposta pelo professor */
unsigned int hashFunctionA(string key, unsigned int maxSize);

/* Funcao Hash buscada de outra fonte */
unsigned int hashFunction(string key, unsigned int maxSize);

/* Insere na lista com tratamento de colisao por busca linear */
bool linearInsert(cell* table, unsigned int maxSize, string key, int data);

/* Busca na lista com tratamento de colisao por busca linear */
int linearSearch(cell* table, unsigned int maxSize, string key);

/* Rehash a lista com tratamento de colisao por busca linear */
bool linearRehash(cell* table[2], bool alt, unsigned int maxSize, string key, int data);

/* Visualizacao tosca da lista ... linear, melhor para tabelas pequenas */
void displayLinear(cell *table, unsigned int maxSize);

/* Insere na lista com tratamento de colisao por encadeamento */
bool linkedInsert(linkedCell* table, unsigned int maxSize, string key, int data, unsigned int * size);

/* Busca na lista com tratamento de colisao por encadeamento */
int linkedSearch(linkedCell* table, unsigned int maxSize, string key);

/* Rehash a lista com tratamento de colisao por encadeamento */
bool linkedRehash(linkedCell* table[2], bool alt, unsigned int maxSize, string key, int data, unsigned int * size);

/* Visualizacao tosca da lista ... encadeamento */
void displayLinked(linkedCell *table, unsigned int maxSize);

unsigned int RSHash  (char* str, unsigned int len);
unsigned int JSHash  (char* str, unsigned int len);
unsigned int PJWHash (char* str, unsigned int len);
unsigned int ELFHash (char* str, unsigned int len);
unsigned int BKDRHash(char* str, unsigned int len);
unsigned int SDBMHash(char* str, unsigned int len);
unsigned int DJBHash (char* str, unsigned int len);
unsigned int DEKHash (char* str, unsigned int len);
unsigned int BPHash  (char* str, unsigned int len);
unsigned int FNVHash (char* str, unsigned int len);
unsigned int APHash  (char* str, unsigned int len);
