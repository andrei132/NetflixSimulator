/*GIRNET Andrei - 311CB*/

#ifndef _LISTA_
#define _LISTA_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Typrdef-urile functiilor 

typedef int cmpFunc(void *, void *);
typedef void afiElemFunc(void *, FILE *);
typedef void* initElemFunc(void *);
typedef void freeElemFunc(void * );


//Structura unei celule a listei simple inlantuite
typedef struct celulaL {
    
    void *info;
    struct celulaL *urm;

} CelulaL, *TLSI;


//Functii liste simplu inlantuite

TLSI initCelula(void *);
void insertStart(TLSI *,TLSI, TLSI);
void showList(TLSI, afiElemFunc ,FILE *);
int insertOrdonat(TLSI *, TLSI, cmpFunc);
void* findList(TLSI *, void *, cmpFunc, int);
void insertPos(TLSI *, TLSI, freeElemFunc, int);
void freeList(TLSI *,freeElemFunc);

#endif