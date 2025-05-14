#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pilha{
    int info;
    struct pilha *prox;
}TPilha;

typedef TPilha *Ppilha;

Ppilha push(Ppilha pilha, int n){
    Ppilha novo;
    novo = (Ppilha)malloc(sizeof(TPilha));
    novo->info = n;
    novo->prox = pilha;
    return novo;
}

Ppilha pop(Ppilha pilha, int *n){
    Ppilha p;
    if(pilha == NULL) 
        return pilha;
    p = pilha;
    *n = p->info; 
    pilha = p->prox;
    free(p);
    return pilha;
}

void imprime(Ppilha pilha){
    Ppilha p;
    for(p=pilha; p!=NULL; p=p->prox){
        printf("%d", p->info);
    }
}

void libera(Ppilha pilha){
    Ppilha p;
    for(p=pilha; p!=NULL; p=pilha){
        pilha = p->prox;
        free(p);
    }
}

int main(){
    int valor, r, i;
    Ppilha pilha = NULL;

    printf("Digite um inteiro: ");
    scanf("%d", &valor);

    for(i=valor; i>0; i=i/2){
        pilha = push(pilha, i%2);
    }

    imprime(pilha);
    libera(pilha);
}
