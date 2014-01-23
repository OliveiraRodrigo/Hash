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

#define initialSize 100
#define expansionFactor 2.0
#define loadFactor 0.43 // 0.0 <= x <= 1.0

#define False 0
#define True  1
#define OFF   0
#define ON    1
#define START 0
#define GET   1
#define STOP  2

double timer(char n, char mark);

void display(linkedCell *table, unsigned int size);

unsigned int hashFunctionA(char key[151], unsigned int tableSize);

unsigned int hashFunction(char key[151], unsigned int tableSize);

int linearInsert(cell* table, unsigned int size, char key[151], int data);

int linearSearch(cell* table, unsigned int size, char key[151]);

int linearRehash(cell* table[2], short alt, unsigned int size, char key[151], int data);

char linkedInsert(linkedCell* table, unsigned int size, char key[151], int data, unsigned int * retSize);

int linkedSearch(linkedCell* table, unsigned int size, char key[151]);

char linkedRehash(linkedCell* table[2], short alt, unsigned int size, char key[151], int data, unsigned int * retSize);
