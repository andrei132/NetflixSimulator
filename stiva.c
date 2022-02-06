/*GIRNET Andrei - 311CB*/

#include "stiva.h"

//Functia de intializare a unei stive
TStiva initStiva(){

    TStiva stiva;
    
    stiva = calloc(1,sizeof(Stiva));
    if (!stiva) return NULL;
    
    return stiva;

}   

//Extrage celula din virf modificind virful 
void* extrageStiva(TStiva stiva){

    void *flag;
    
    if(VIDAS(stiva)) return NULL;

    flag = VRFS(stiva);
    VRFS(stiva)=VRFS(stiva)->urm;

    return flag;

}

//Insereaza intro stiva
int insertStiva(TStiva stiva, TLSI celula){

    if(!celula) return 0;
    
    celula->urm = VRFS(stiva);
    VRFS(stiva) = celula;
    
    return 1;
}

//Rastoarna o stiva
int rastoarnaStiva(TStiva stiva){

    TStiva res= initStiva();
    TLSI aux ;

    if(!res) return -1;

    while (!VIDAS(stiva)) {
        
        aux = (TLSI)extrageStiva(stiva);
        insertStiva(res,aux);

    }
    
    memcpy(&VRFS(stiva),&VRFS(res),sizeof(TLSI));
    free(res);

    return 0;
}

//Gaseste intr-o stiva informatia dorita si o elimina dupa dorinta
void* findStiva(TStiva stiva,void* info, cmpFunc cmp,int elim){

    TStiva aux=initStiva();
    TLSI elem,res=NULL;

    if(!aux) return NULL;

    while (!VIDAS(stiva)){
        
        elem = (TLSI)extrageStiva(stiva);
        
        if(!cmp(elem->info,info)){

            res = elem;

            if(!elim){

                insertStiva(aux,elem);

            }

        } else{
            
            insertStiva(aux,elem);

        }

    }
    
    rastoarnaStiva(aux);
    memcpy(&VRFS(stiva),&VRFS(aux),sizeof(TLSI));
    free(aux);

    return res;
    
}

//Functia de afisare a unei stive
void showStiva(TStiva stiva,void afiElement(void *a,FILE*),FILE *fout){
    
    TLSI celula;

    if(VIDAS(stiva)){
        
        fprintf(fout," [].\n");
        return;
    
    }

    TStiva aux = initStiva();
    if(!aux) return;

    fprintf(fout," [");

    while (!VIDAS(stiva)) {
        
        celula = extrageStiva(stiva);
        afiElement(celula->info,fout);
        fprintf(fout,", ");
        insertStiva(aux,celula);

    }
    
    rastoarnaStiva(aux);

    memcpy(&VRFS(stiva),&VRFS(aux),sizeof(TLSI));
    free(aux);
    fseek(fout,-2,1);
    fprintf(fout,"].\n");
    
}

//Dezaloca o stiva
void freeStiva(TStiva *stiva,void freeElement(void*)){
    
    TLSI aux;

    while (!VIDAS(*stiva)){
        
        aux = (TLSI)extrageStiva(*stiva);
        freeElement(&aux->info);
        free(aux);  
    
    }

    free(*stiva);
    
}