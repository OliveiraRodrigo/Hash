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
#include <string.h>

typedef struct{
    char index[200];
    char key[151];
    int data;
    int filled; //ocupada
} cell;

#define INSERT 0
#define SEARCH 1
#define REHASH 2

#define initialSize 100
#define expansionFactor 2.0
#define loadFactor 0.7

unsigned int hashFunction(char key[151], unsigned int tableSize);

int insert(cell* table, unsigned int size, char key[151], int data);

int search(cell* table, unsigned int size, char key[151]);

int rehash(cell* table, unsigned int size, char key[151], int data);
