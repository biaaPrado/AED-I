#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int bit;
    struct No* prox;    
}No;

typedef struct Pilha{
    No* topo;
}Pilha;

No* criaNo(int bit){
    No* novo = malloc(sizeof(No));
    novo->bit = bit;
    novo->prox = NULL;
    return novo;
}

void push(Pilha* p, int bit){
    No* novo = criaNo(bit);
    novo->prox = p->topo;
    p->topo = novo;
}

int pop(Pilha* p){
    if(p->topo == NULL) return 0;

    No* temp = p->topo;
    int bit = temp->bit;
    p->topo = temp->prox;
    free(temp);
    return bit;
}

No* somaUm(No* no, int* vaiUm){
    if(no == NULL && *vaiUm == 1)
        return criaNo(1);
    else if(no == NULL)
        return NULL;

    no->prox = somaUm(no->prox, vaiUm);

    int soma = no->bit + *vaiUm;
    no->bit = soma%2;
    *vaiUm = soma/2;

    return no;
}

void libera(No* lista){
    while (lista != NULL){
        No* temp = lista;
        lista = lista->prox;
        free(temp);
    }
    
}

int main(){
    Pilha p = {NULL};
    int bit;

    while(scanf("%d", &bit) && bit != -1){
        push(&p, bit);   
    }

    No* lista = NULL;
    No* fim = NULL;
    while(p.topo != NULL){
        No* novo = criaNo(pop(&p));
        if (lista == NULL)
            lista = fim = novo;
        else{
            fim->prox = novo;
            fim = novo;
        }
    }

    int vaiUm = 1;
    lista = somaUm(lista, &vaiUm);

    No* atual = lista;    
    while(atual != NULL){
        printf("%d", atual->bit);
        atual = atual->prox;
    }

    libera(lista);
    return 0;
}