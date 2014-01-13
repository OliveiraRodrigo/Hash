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
    char key[200];
    unsigned int data;
    int filled; //ocupada
} cell;

int insert(cell* table, unsigned int size, char key[200], unsigned int data);

unsigned int search(cell* table, unsigned int size, char key[200]);

unsigned int hashFunction(char key[200], unsigned int tableSize);
