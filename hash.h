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
    char index[200];
    char key[151];
    int data;
    short filled; //ocupada
} cell;

typedef struct node{
    char key[151];
    int data;
    struct node * next;
} node;

typedef struct{
    char index[200];
    short filled; //ocupada
    node * first;
} linkedCell;

#define initialSize 100
#define expansionFactor 2.0
#define loadFactor 0.8

#define OFF   0
#define ON    1
#define START 0
#define GET   1
#define STOP  2

double timer(short n, short mark);

unsigned int hashFunctionA(char key[151], unsigned int tableSize);

unsigned int hashFunction(char key[151], unsigned int tableSize);

int linearInsert(cell* table, unsigned int size, char key[151], int data);

int linkedInsert(linkedCell* table, unsigned int size, char key[151], int data);

int linearSearch(cell* table, unsigned int size, char key[151]);

int linearRehash(cell* table, unsigned int size, char key[151], int data);
