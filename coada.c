/*GIRNET Andrei - 311CB*/

#include "coada.h"

//Functia de intializare intr-o coada
TCoada initCoada(){
    
    TCoada coada;
    coada = calloc(1,sizeof(Coada));
    if (!coada) return NULL;

    coada->nrElemente = 0;
    VRFC(coada) = NULL;
    BAZC(coada) = NULL;

    return coada;

}

//Inserarea intr-o coada
int insertCoada(TCoada coada, TLSI celula){
    
    if(!celula) return 0;

    coada->nrElemente++;

    if(VIDAC(coada)){

        VRFC(coada)= BAZC(coada) = celula;

        return 1;

    }

    BAZC(coada)->urm = celula;
    BAZC(coada) = celula;

    return 1;
    
}

//Modifica virful cozii
void* extrageCoada(TCoada coada){

    void *flag;
    
    if (VIDAC(coada)){

        return NULL;

    }
    
    flag = VRFC(coada);
    VRFC(coada)=VRFC(coada)->urm;
    coada->nrElemente--;

    return flag;

}

/*Cauta in coada o inforamtie si intoarce 
adresa celulei elimindo din coada daca se cere*/
void* findCoada(TCoada coada,void *info,cmpFunc cmp,int elim,
                freeElemFunc freeElement){

    TCoada aux = initCoada();
    TLSI elem,res=NULL;

    if(!aux) return NULL;
    
    while (!VIDAC(coada)){
        
        elem = (TLSI)extrageCoada(coada);
        
        
        if(!cmp(elem->info,info)){

            res = elem;

            if(!elim){

                insertCoada(aux,elem);

            }

        } else{

            insertCoada(aux,elem);
        
        }
    
    }

    if(VIDAC(aux)){
        
        //copierea unei cozi in alta
        memcpy(&VRFC(coada),&VRFC(aux),sizeof(TLSI));
        memcpy(&BAZC(coada),&BAZC(aux),sizeof(TLSI));
        coada->nrElemente=0;
        free(aux);

        return res;

    }

    BAZC(aux)->urm = NULL;

    //copierea unei cozi in alta
    memcpy(&VRFC(coada),&VRFC(aux),sizeof(TLSI));
    memcpy(&BAZC(coada),&BAZC(aux),sizeof(TLSI));
    coada->nrElemente=aux->nrElemente;
    free(aux);

    return res;

}

// Functia de afisare a unei cozi
void showCoada(TCoada coada,afiElemFunc afiElement,FILE *fout){
    
    TLSI flag;

    if(VIDAC(coada)) {
    
        fprintf(fout," [].\n");
        return;
    
    }

    TCoada aux = initCoada();
    if (!aux) return;

    fprintf(fout," [");

    while (!VIDAC(coada)){
        
        flag = extrageCoada(coada);
        afiElement(flag->info,fout);
        fprintf(fout,", ");
        insertCoada(aux,flag);

    }   

    fseek(fout,-2,1);
    fprintf(fout,"].\n");

    //copierea unei cozi in alta
    memcpy(&VRFC(coada),&VRFC(aux),sizeof(TLSI));
    memcpy(&BAZC(coada),&BAZC(aux),sizeof(TLSI));
    coada->nrElemente=aux->nrElemente;
    free(aux);
    
}

//Functia de dezalocare a unei cozi
void freeCoada(TCoada *coada,void freeElement(void*)){

    TLSI aux;

    while (!VIDAC(*coada)){
        
        aux=(TLSI)extrageCoada(*coada);
        freeElement(&aux->info);
        free(aux);
    
    }
    
    free(*coada);

}