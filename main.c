/*GIRNET Andrei - 311CB*/

#include "general.h"

//Functia de dezalocare a unei adrese a unui int, primeste &(int*)
void freeInt(void* a){
    
    free(*(int**)a);

}

//Functia de dezaloare a unui serial chiar daca e aloc doar partial
void freeFunction(void* a){

    Serial *x = *(Serial**)a;
   

    //Daca e alocat Numele
    if(x->nume){

        free(x->nume);

    }

    //Daca e alocata coada cu sezoane
    if(x->Sezoane) {

        TLSI b;
        TCoada v;
        
        while (!VIDAC(x->Sezoane)){
            
            b = ((TLSI)extrageCoada(x->Sezoane));
            v = (TCoada)b->info;
            
            freeCoada(&v,freeInt);
            free(b);
       
        }
        
        free(x->Sezoane);

    }

    //daca e alocata structura
    if(x){

        free(x);
    }

}

//Creea si initializarea unui serial
void* initSerial(void *a){

    Serial *res;
    int i, j, pos;
    int nrSezoane;
    int aux, *aux2, sum = 0;
    char *buff = (char *)a;

    if(!buff){

        return NULL;

    }

    res = calloc(1,sizeof(Serial));
    
    if (!res){

        return NULL;

    }

    res->nume = calloc(MAX_CHR + 1,sizeof(char));
    
    if (!res->nume){

        free(res);
        return NULL;

    }

    //%n memoreaza cite carctere au fost citite din buff, si scrie la pos
    sscanf(buff,"%s%n",res->nume,&pos);
    buff += pos;

    //Daca se va cere doar cautarea dupa nume
    if(*buff == '\0'){

        res->rating = -1;
        return res;

    }

    sscanf(buff,"%f%n",&(res->rating),&pos);
    buff += pos;
    
    sscanf(buff,"%d%n",&nrSezoane,&pos);
    buff += pos;
    
    res->Sezoane = initCoada();
    if(!res->Sezoane) {

        freeFunction(res);
        return NULL;
    }

    TCoada Serii;

    for(i = 0; i < nrSezoane; i++ ){

        sscanf(buff,"%d%n",&aux,&pos);
        buff += pos;
        
        Serii = initCoada();
        if(!Serii) {

            freeFunction(res);
            return NULL;

        }

        if (!insertCoada(res->Sezoane,initCelula(Serii))) {
            
            freeFunction(res);
            return NULL;

        }
        
        for(j = 0; j < aux; j++){

            aux2=calloc(1,sizeof(int));
            if(!aux2){
                
                freeFunction(res);
                return NULL;

            }

            sscanf(buff,"%d%n",aux2,&pos);;
            
            if(!insertCoada(Serii,initCelula(aux2))){

                freeFunction(res);
                return NULL;

            }
            
            buff += pos;
            sum = sum + *aux2;

        }
        
    }

    res->nrMin = sum;
    res->nrMinVizionate = 0;

    return res;
    
}

//Functia de afisare a informatiiei
void afiElement(void *a, FILE *fout){

    Serial *x = (Serial *)a;
    
    fprintf(fout,"(%s, %.1f)",x->nume,x->rating);

}

//Functia de comparatie a 2 seriale
int cmp(void *a, void *b){

    Serial *x = (Serial*)a;
    Serial *y = (Serial*)b;
    int cmp;

    //Daca se cere cautarea dupa nume
    if((x->rating == (float)-1) || (y->rating == (float)-1)){

        cmp = 0;
        
    } else{
        
        cmp = (int)((y->rating - x->rating)*100);
        
    }

    if (!cmp){

        return strcmp(x->nume,y->nume);

    } 

    return cmp;

}

int main(int argc, char* argv[]){

    FILE *fin, *fout;

    fin=fopen(argv[1], "r");
    fout=fopen(argv[2], "w");

    if(!fin || !fout){

        return 1;

    }

    prelucrareaFisierului(fin, fout, freeFunction, initSerial, afiElement, cmp, freeInt);

    fclose(fin);
    fclose(fout);

    return 0;
}