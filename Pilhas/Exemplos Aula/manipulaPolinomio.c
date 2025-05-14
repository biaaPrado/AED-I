#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    float coef;
    int expo;
    struct lista *prox;
}TLista;

typedef TLista*PLista;

PLista insere(PLista l, float c, int e){
    PLista novo = (PLista)malloc(sizeof(TLista));
    novo->coef = c;
    novo->expo = e;
    novo->prox = l;
    return(novo);
}

void imprime(PLista l){
    PLista p;
    int primeiro = 1;

    for(p=l; p!=NULL; p=p->prox){
        if(!primeiro && p->coef>0)
            printf("+");

        printf("%.0f",  p->coef);

        
        if(p->expo > 1)
            printf("x^%d", p->expo);
        else if(p->expo == 1)
            printf("x");

        primeiro = 0;
    }
    printf("\n");
}

void libera(PLista l){
    PLista aux; 
    while (l!=NULL){
        aux = l;
        l = l->prox;
        free(aux);    
    }
    
}

PLista somaPolinomios(PLista l1, PLista l2){
    PLista lr = NULL;

    while(l1 != NULL && l2 != NULL){
        if(l1->expo < l2->expo){
            lr = insere(lr, l1->coef, l1->expo);
            l1 = l1->prox;
        }else if(l2->expo < l1->expo){
            lr = insere(lr, l2->coef, l2->expo);
            l2 = l2->prox;
        }else{
            float soma = l1->coef+l2->coef;
            if(soma!=0)
                lr = insere(lr, soma, l1->expo);
            l1 = l1->prox;
            l2 = l2->prox;
        }
    }

    while(l1!=NULL){
        lr = insere(lr, l1->coef, l1->expo);
        l1 = l1->prox;
    }
    while(l2!=NULL){
        lr = insere(lr, l2->coef, l2->expo);
        l2 = l2->prox;
    }

    return lr;
}

int main(){
    PLista l1 = NULL, l2 = NULL, lr = NULL;
    float coef;
    int expo;

    printf("Digite o primeiro polinomio (termine com 99999): \n");

    do{
        printf("Digite o coeficiente:");
        scanf("%f", &coef);
        if(coef != 99999){
            printf("Digite o expoente:");
            scanf("%d", &expo);
            l1 = insere(l1, coef, expo);
        }
    }while(coef!=99999);

    printf("Digite o segundo polinomio (termine com 99999): \n");

    do{
        printf("Digite o coeficiente:");
        scanf("%f", &coef);
        if(coef != 99999){
            printf("Digite o expoente:");
            scanf("%d", &expo);
            l2 = insere(l2, coef, expo);
        }
    }while(coef!=99999);

    lr = somaPolinomios(l1, l2);

    printf("Polinômio resultante:\n");
    imprime(lr);

    libera(l1);
    libera(l2);
    libera(lr);

    return 0;
}