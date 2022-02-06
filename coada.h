/*GIRNET Andrei - 311CB*/

#include "lista.h"

#ifndef _COADA_
#define _COADA_


//Define-uri utile

#define VRFC(a) (((TCoada)a)->vrf)
#define BAZC(a) (((TCoada)a)->bz)
#define VIDAC(a) (VRFC(a) == NULL)


//Structura unei cozi
typedef struct coada {

    TLSI vrf, bz;
    int nrElemente;

}Coada, *TCoada;


//Functii utile

TCoada initCoada();
int insertCoada(TCoada, TLSI);
void *extrageCoada(TCoada);
void showCoada(TCoada, afiElemFunc, FILE *);
void* findCoada(TCoada, void *, cmpFunc, int, freeElemFunc);
void freeCoada(TCoada *, freeElemFunc);

#endif