/*GIRNET Andrei - 311CB*/

#include "lista.h"

#ifndef _STIVA_
#define _STIVA_

//Define-uri utile

#define VRFS(a) (((TStiva)(a))->vrf)
#define VIDAS(a) (VRFS(a) == NULL)


//Structura unei stive

typedef struct stiva {
    
    TLSI vrf;

}Stiva, *TStiva;


//Functii Utile

TStiva initStiva();
void* extrageStiva(TStiva);
int insertStiva(TStiva, TLSI);
int rastoarnaStiva(TStiva);
void showStiva(TStiva, afiElemFunc, FILE *);
void* findStiva(TStiva, void *, cmpFunc, int);
void freeStiva(TStiva *, freeElemFunc);

#endif