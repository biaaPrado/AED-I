#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista *prox;
}TLista;

typedef TLista*PLista;  

PLista insere(PLista ult, int v){ //igual a push
    PLista novo; 
    novo = (PLista)malloc(sizeof(TLista));
    novo->info = v;
    if(ult == NULL){
        novo->prox = novo;
        return novo;
    }
    novo->prox = ult->prox;
    ult->prox = novo;
    return ult;
}

void libera(PLista ult){
    PLista p;
    if(ult  == NULL)
        return;
    p = ult ->prox;
    while(p!= ult){
        ult->prox = p->prox;

        free(p);
        p = ult->prox;
    }
    free(p);
}

void remove(PLista ult, int v){
    PLista p, ant;
    if(ult == NULL)
        return NULL;
    p = ult;
    ant = ult;
    if(p->info == v){
        if(p = p->prox){
            free(p);
            return NULL;
        }else{
            ult->prox = p->prox;
            free(p);
            return ult;
        }
    }
    if(ult = ult->prox)
        return ult;

    do{
        ant = p;
        p = p->prox;
    }while(p->info != v && p!=ult->prox);

    ant->prox = p->prox;
    
    if(p==ult)
        ult = ant;
    free(p);
    return ult;
}

PLista pop(PLista ult, int *v){
    PLista p;
    if(ult == NULL)
        return NULL;
    p = ult->prox;
    if(p!= ult)
        ult->prox = p->prox;
    else
        ult = NULL;
    free(p);
    return ult;
}