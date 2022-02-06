/*GIRNET Andrei - 311CB*/

#include "coada.h"
#include "coada.h"
#include "stiva.h"
#include "lista.h"

#ifndef _GENERAL_
#define _GENERAL_

#define MAX_CHR 32

//Structura unui serial
typedef struct serial {
    
    int nrMin,nrMinVizionate;
    TCoada Sezoane;
    char *nume;
    float rating;

}Serial;


//Functie de prelucrare fisier

void prelucrareaFisierului(FILE *,FILE *,freeElemFunc,initElemFunc,afiElemFunc,
                            cmpFunc,freeElemFunc);

#endif