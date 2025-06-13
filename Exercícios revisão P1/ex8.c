#include <stdio.h>
#include <stdlib.h>

typedef struct lista2 {
    char num_tel[11];
    float custo;
    struct lista2 *prox, *ant;
}TLista2;

typedef TLista2 *PLista2;

PLista2 insere(PLista2 lista, char num_tel[], float custo){
    PLista2 novo, p;
    novo = (PLista2)malloc(sizeof(TLista2));
    strcpy(novo->num_tel,num_tel);
    novo->custo = custo;
    if (lista==NULL){
        novo->ant = novo->prox = NULL;
        return(novo);
    }
    for (p=lista; p->prox!=NULL && custo<=p->custo; p=p->prox){
        if(p->custo<custo) { //insere antes de p
            novo->prox = p;
            novo->ant = p->ant;
            p->ant = novo;
            if(p!=lista){
                novo->ant->prox = novo;
                return(lista);
            }
            return(novo);
        } else{ //insere no fim
            novo->prox = p->prox;
            novo->ant = p;
            p->prox = novo;
            return(lista);
        }
    }
}