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
    if (c==0)
        return l;
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
    PLista lr = NULL, q1, q2;

    if(l1==NULL && l2==NULL)
        return NULL;

    q1 = l1, q2 = l2;

    while(q1 != NULL || q2 != NULL){
        if(q1  == NULL || (q2!=NULL && q1->expo > q2->expo)){
            lr = insere(lr, q2->coef, q2->expo);
            q2 = q2->prox;
        }else if(q2==NULL || (q1!=NULL && q1->expo < q2->expo)){
            lr = insere(lr, q1->coef, q1->expo);
            q1 = q1->prox;
        }else{
            q1 != NULL, q2 != NULL;
            lr = insere(lr, q1->coef+q2->coef, q1->expo);
            q1 = q1->prox;
            q2 = q2->prox;
        }
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