/* 
 * File:   hash.h
 * Author: Rodrigo
 *
 * Created on 17 de Dezembro de 2013, 14:46
 */

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
    int filled; //ocupada
} cell;

#define initialSize 100
#define expansionFactor 2.0
#define loadFactor 0.8

#define OFF   0
#define ON    1
#define START 0
#define GET   1
#define STOP  2

unsigned int hashFunction(char key[151], unsigned int tableSize);

int insert(cell* table, unsigned int size, char key[151], int data);

int search(cell* table, unsigned int size, char key[151]);

int rehash(cell* table, unsigned int size, char key[151], int data);

double timer(short n, short mark);