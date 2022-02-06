/*GIRNET Andrei - 311CB*/

#include "general.h"

//Functia de adaugare a unui element intr-o lista ordonata
int add(TLSI *array, char *buff, initElemFunc initSerial, cmpFunc cmp,
        freeElemFunc freeFunction, FILE *fout){

    int pos,chr;

    sscanf(buff, "%d%n", &pos, &chr);
    if(pos > 3) return -1;
    buff += chr;
    void *info = initSerial(buff);
    
    if(!info) return -1;

    TLSI celula = initCelula(info);
    
    if(!celula){

        freeFunction(info);
        return -2;

    }

    int i = insertOrdonat((array + pos - 1), celula, cmp);

    fprintf(fout, "Serialul %s a fost adaugat la pozitia %d.\n",
            ((Serial*)celula->info)->nume, i + 1);

    return 0;

}

//Functia de inserarea a unei informatii in lista la o pozitie anumita
int addTop(TLSI *top, char *buff, initElemFunc initSerial, cmpFunc cmp,
            FILE *fout, afiElemFunc afiElement,freeElemFunc freeFunction){
    
    int pos,chr;
    
    sscanf(buff,"%d%n",&pos,&chr);
    if(pos > 10) return -1;
    buff += chr;
    void *info = initSerial(buff);  
    if(!info) return -1;

    TLSI celula = initCelula(info);
    if(!celula){

        freeFunction(info);
        return -2;

    }

    insertPos(top,celula,freeFunction,pos);

    return 0;

}

//Adauga un sezon la un serial care nu se afla in hystory
int addSez(TLSI* array, TLSI top10, TCoada wLater, TStiva cWatch, char *buff,
            cmpFunc cmp, initElemFunc initSerial, freeElemFunc freeFunction,
            FILE* fout,freeElemFunc freeInt){
    
    char *nume = calloc(MAX_CHR + 1,sizeof(char));
    int chr,nrEpisoade,*nrMIn,i;

    sscanf(buff,"%s%n",nume,&chr);
    buff += chr;
    void *info = initSerial(nume);
    free(nume);
    if(!info) return -1;

    TLSI res = findStiva(cWatch, info, cmp, 0);
    if(!res) res = findList(array, info, cmp, 0); 
    if(!res) res = findList(array + 1, info, cmp, 0);
    if(!res) res = findList(array + 2, info, cmp, 0);
    if(!res) res = findList(&top10, info, cmp, 0);
    if(!res) res = findCoada(wLater, info, cmp, 0, freeFunction);

    freeFunction(&info);
    
    if(!res) return -2;

    sscanf(buff,"%d%n",&nrEpisoade,&chr);
    buff += chr;

    TCoada Serii = initCoada();
    if(!Serii) return -1;

    if(!insertCoada(((Serial*)res->info)->Sezoane,initCelula(Serii))){

        freeCoada(&Serii,freeInt);
        return -1;
        
    }

    for(i = 0; i < nrEpisoade; i++){
        
        nrMIn = calloc(1,sizeof(int));
        sscanf(buff, "%d%n", nrMIn, &chr);
        buff += chr;
        if(!insertCoada(Serii,initCelula(nrMIn))){

            freeCoada(&Serii,freeInt);
            return -1;

        }

        ((Serial*)res->info)->nrMin += *nrMIn;

    }

    fprintf(fout,"Serialul %s are un sezon nou.\n",((Serial*)res->info)->nume);

    return 0;

}

//Insereaza in coada watch later un element cu info dorit daca exista alte liste
int later(TLSI *array,TLSI *top10,TCoada wLater,TStiva cWatch,char *buff,
            cmpFunc cmp,initElemFunc initSerial,freeElemFunc freeFunction,
            FILE* fout){

    char *nume = calloc(MAX_CHR + 1,sizeof(char));
    int chr;

    sscanf(buff,"%s%n",nume,&chr);
    buff += chr;
    void *info = initSerial(nume);
    free(nume);
    if(!info) return -1;

    TLSI res = findStiva(cWatch, info, cmp, 1);
    if(!res) res = findList(array, info, cmp, 1); 
    if(!res) res = findList(array + 1, info, cmp, 1);
    if(!res) res = findList(array + 2, info, cmp, 1);
    if(!res) res = findList(top10, info, cmp, 1);
    if(!res) res = findCoada(wLater, info, cmp, 1, freeFunction);
    
    freeFunction(&info);
    
    if(!res) return -2;

    insertCoada(wLater, res);

    fprintf(fout,"Serialul %s se afla in coada de asteptare pe pozitia %d.\n",
            ((Serial*)res->info)->nume, wLater->nrElemente);

    return 1;

}

//Muta un serial in cWatch, iar daca deja exista il pune in virful stivei
int watch(TLSI *array,TLSI *top10,TCoada wLater,TStiva cWatch,TStiva hyst,
            char *buff,cmpFunc cmp,initElemFunc initSerial,
            freeElemFunc freeFunction,FILE* fout){

    char *nume = calloc(MAX_CHR + 1, sizeof(char));
    int chr,nrMinVizionat;

    sscanf(buff,"%s%n",nume,&chr);
    buff += chr;
    void *info = initSerial(nume);
    free(nume);
    if (!info) return -1;

    TLSI res = findStiva(cWatch, info, cmp, 1);
    if(!res) res = findList(array, info, cmp, 1); 
    if(!res) res = findList(array + 1, info, cmp, 1);
    if(!res) res = findList(array + 2, info, cmp, 1);
    if(!res) res = findList(top10, info, cmp, 1);
    if(!res) res = findCoada(wLater, info, cmp, 1, freeFunction);

    freeFunction(&info);

    if(!res) return -2;
    
    sscanf(buff,"%d",&nrMinVizionat);
    ((Serial*)res->info)->nrMinVizionate += nrMinVizionat;
    
    //Daca sa depasit timpul pentru vizionare
    if( ((Serial*)res->info)->nrMin <= ((Serial*)res->info)->nrMinVizionate ){

        fprintf(fout,"Serialul %s a fost vizionat integral.\n",
                ((Serial*)res->info)->nume);
        
        insertStiva(hyst,res);
    
    } else {

        insertStiva(cWatch,res);

    }

    return 0;

}


//Functia de prelucrare a unui fisier
void prelucrareaFisierului(FILE *fin, FILE *fout, freeElemFunc freeFunction,
                            initElemFunc initSerial, afiElemFunc afiElement,
                            cmpFunc cmp,freeElemFunc freeInt){

    TLSI *array;
    TLSI top10=NULL;
    TCoada wLater = initCoada();;
    TStiva cWatch = initStiva();
    TStiva history = initStiva();
    char *buff,*flag,*comm;
    int pos;

    array = calloc(3,sizeof(TLSI));
    buff = calloc(256,sizeof(char));

    if(!buff){
        
        return ;
    
    }

    comm = calloc(20,sizeof(char));

    if(!comm){
        
        free(buff);
        return ;

    }

    flag = buff;

    while (fgets(buff,255,fin) != NULL){

        
        if(buff[strlen(buff)-1] == '\n') {
            
            buff[strlen(buff)-1] = '\0';
        
        }

        sscanf(buff,"%s%n",comm,&pos);
        buff += pos;

        //Recunoasterea comenzilor

        if (!strcmp(comm,"add")){

            add(array,buff,initSerial,cmp,freeFunction,fout);

        }
        
        if (!strcmp(comm,"add_sez")){

            addSez(array,top10,wLater,cWatch,buff,cmp,initSerial,
                    freeFunction,fout,freeInt);

        }

        if (!strcmp(comm,"add_top")){

            addTop(&top10,buff,initSerial,cmp,fout,afiElement,freeFunction);
            fprintf(fout,"Categoria top10:");
            showList(top10,afiElement,fout);

        }
        
        if (!strcmp(comm,"later")){

            later(array,&top10,wLater,cWatch,buff,cmp,initSerial,
                    freeFunction,fout);
            
        }

        if (!strcmp(comm,"watch")){

            watch(array,&top10,wLater,cWatch,history,buff,cmp,initSerial,
                    freeFunction,fout);
            
        }

        if (!strcmp(comm,"show")){
         
            if(sscanf(buff,"%d",&pos)){

                fprintf(fout,"Categoria %d:",pos);
                showList(array[pos-1],afiElement,fout);

            }

            if(strstr(buff,"top10")){

                fprintf(fout,"Categoria top10:");
                showList(top10,afiElement,fout);

            }

            if(strstr(buff,"later")){

                fprintf(fout,"Categoria later:");
                showCoada(wLater,afiElement,fout);

            }

            if(strstr(buff,"watching")){

                fprintf(fout,"Categoria watching:");
                showStiva(cWatch,afiElement,fout);

            }

            if(strstr(buff,"history")){

                fprintf(fout,"Categoria history:");
                showStiva(history,afiElement,fout);

            }

        }

        buff = flag;
        
    }

    free(flag);
    free(comm);
    freeList(array,freeFunction);
    freeList(array+1,freeFunction);
    freeList(array+2,freeFunction);
    free(array);
    freeList(&top10,freeFunction);
    freeCoada(&wLater,freeFunction);
    freeStiva(&cWatch,freeFunction);
    freeStiva(&history,freeFunction);

}