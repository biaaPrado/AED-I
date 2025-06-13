#include <stdio.h>
#include <stdlib.h>

typedef struct lista2 {
    float coef;
    int expo;
    struct lista2 *prox, *ant;
}TLista2;

typedef TLista2 *PLista2;
//========================
//Insere em ordem decrescente do expoente
PLista2 insere(PLista2 l, float coef, int expo){
    PLista2 novo, p;
    novo = (PLista2)malloc(sizeof(TLista2));
    novo->coef = coef;
    novo->expo = expo;
    if (l==NULL) {
        novo->prox = NULL;
        novo->ant = NULL;
    return(novo);
    } else {
        for (p=l;p->expo>expo && p->prox!=NULL;p=p->prox);
            if (p->expo>expo) { //insere no final
                novo->prox = NULL;
                novo->ant = p;
                p->prox = novo;
            } else {//insere antes de "p"
                novo->prox = p;
                novo->ant = p->ant;
            if (p!=l)
                p->ant->prox = novo;
                p->ant = novo;
            if(p==l)
                l = novo;
        }
        return(l);
    }
}

//Multiplica dois polinômios
PLista2 multiplica(PLista2 p1, PLista2 p2){
    PLista2 result = NULL, p,q,s;
    int expo;
    if(p1==NULL)
        for(q=p2; q!=NULL; q=q->prox)
            result = insere(result,q->coef,q->expo);
    
    else if(p2==NULL)
        for (p=p1;p!=NULL;p=p->prox)
            result = insere(result,p->coef,p->expo);
    else{
        for (p=p1;p!=NULL;p=p->prox)
            for(q=p2; q!=NULL; q=q->prox){
                expo = p->expo+q->expo;
                s = busca(result,expo); //verifica se já foi inserido este expoente
                if(s==NULL)
                    result = insere(result,p->coef*q->coef,expo);
                else
                    s->coef = s->coef + p->coef*q->coef; //se já existe o expoente, some a multiplicação dos coeficientes
            }
    }
    return (result);
}