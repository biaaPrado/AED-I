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
    if(p->topo == NULL) return -1;

    No* temp = p->topo;
    int bit = temp->bit;
    p->topo = temp->prox;
    free(temp);
    return bit;
}

void incrementaRecursivo(Pilha* p, int carry){
    if(carry == 0) return;

    if(p->topo == NULL){
        push(p, 1);
        return;
    }
    int bit = pop(p);
    int soma = bit + carry;
    incrementaRecursivo(p, soma/2);
    push(p, soma%2);
}

void imprimeBinario(No* no){
    if(no == NULL) return;
    imprimeBinario(no->prox);
    printf("%d", no->bit);
}

void libera(Pilha* p){
    while(p->topo != NULL){
        pop(p);
    }
}

int main(){
    Pilha p = {NULL};
    char c;

    while((c = getchar()) != '\n' && c != EOF){
        if(c == '0' || c == '1')
            push(&p, c - '0');
    }

    incrementaRecursivo(&p, 1);

    imprimeBinario(p.topo);
    printf("\n");

    libera(&p);
    return 0;
}
