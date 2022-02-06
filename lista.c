/*GIRNET Andrei - 311CB*/

#include "lista.h"

//Initializarea si creearea unuei celule a unei liste simplu inlantuite
TLSI initCelula(void *info){

    if(!info) return NULL;
    
    TLSI cel;
    
    cel = malloc(sizeof(CelulaL));
    
    if(!cel){

        return NULL;

    }

    cel->info = info;
    cel->urm = NULL;

    return cel;

}

//Insere inaintea unei liste
void insertStart(TLSI *list, TLSI anter, TLSI insert){

    if (anter){

        anter->urm = insert;

    }
    
    insert->urm = *list;
    *list = insert;
    
}

//Functia de inserare ordonata intro lista ordonata dupa functia cmp
int insertOrdonat(TLSI *list, TLSI insert, cmpFunc cmp){

    TLSI aux,ant = NULL;
    int i;
    aux=*list;

    //Inserarea la inceput
    if (!(*list) || (cmp(insert->info,(aux)->info) < 0)){

        insertStart(list,NULL,insert);

        return 0;

    }

    for(i = 0; aux != NULL; aux = (aux)->urm, i++){

        if (cmp(insert->info,(aux)->info) < 0){

            insertStart(&aux,ant,insert);

            return i;

        }
        
        ant = aux;
    }

    //Inserarea la sfirsit
    insertStart(&aux,ant,insert);

    return i;

}

//Parcurge o lista si se opreste la al 10-lea element sau la sfarsitul listei
TLSI first10(TLSI list){

    int i;

    for(i = 0;(list!=NULL) && (i<9);list=list->urm,i++);

    return list;

}

//Inserarea la o pozitie anumita in lista
void insertPos(TLSI *list,TLSI insert,freeElemFunc freeElement,int pos){

    TLSI aux=*list;
    int i;

    //Inserarea la in ceput
    if(pos == 1){

        insert->urm=*list;
        *list=insert;
        aux = first10(*list);

        if(aux){

            freeList(&aux->urm,freeElement);

        }

        return;
    }
    
    for(i = 2; (i < pos) && (aux != NULL); i++, aux=aux->urm);
    
    if(!aux) return;
    
    insert->urm = aux->urm;
    aux->urm = insert;

    

    aux = first10(*list);

    if(aux){

        freeList(&aux->urm,freeElement);

    }

        return ;

}

//Intoarce pointerul la celula cu informatia dorita si il sterge dupa dorinta
void* findList(TLSI *list, void *info, cmpFunc cmp,int elim){

    TLSI aux,ant;
    ant = NULL;
    aux = *list;

    for(;(aux != NULL) ;aux=aux->urm){
        
        //A fost gasit elementul
        if(!cmp(aux->info,info)){
            
            //Se cere eliminarea
            if(elim){

                if(ant == NULL){
                    
                    *list = (*list)->urm;
                
                } else{
                    
                    ant->urm=aux->urm;

                }

                aux->urm=NULL;
            
            }
            
            return aux;

        }
        
        ant = aux;
    }

    return NULL;

}

//Afisarea unei liste
void showList(TLSI list, afiElemFunc afiElement,FILE *fout){

    if(!list){
        
        fprintf(fout," [].\n");
        return;
    
    }

    fprintf(fout," [");
    
    for ( ; list != NULL; list = list->urm ){

        afiElement(list->info,fout);
        fprintf(fout,", ");

    }
    
    fseek(fout,-2,1);
    fprintf(fout,"].\n");

}

//Functia de dezaloacare a unei memorii
void freeList(TLSI *list,void freeElement(void*)){

    TLSI aux;

    for(;*list != NULL;){

        aux = *list;
        *list=(*list)->urm;

        freeElement(&aux->info);
        
        free(aux);

    }
    

}