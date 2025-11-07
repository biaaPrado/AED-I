//4.6.2 Escreva uma versão da função BuscaEInsere para listas encadeadas sem cabeça.

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int conteudo;
    struct No *prox;
} No;

No *BuscaEInsere(int x, No **lista) {
    No *p, *q, *nova;

    p = NULL;
    q = *lista;

    // Percorre até encontrar x ou o fim da lista
    while (q != NULL && q->conteudo < x) {
        p = q;
        q = q->prox;
    }

    // Se já existe o valor, apenas retorna o ponteiro
    if (q != NULL && q->conteudo == x)
        return q;

    // Cria nova célula
    nova = (No *) malloc(sizeof(No));
    nova->conteudo = x;
    nova->prox = q;

    // Insere no início ou no meio/fim
    if (p == NULL)
        *lista = nova;     // insere no início
    else
        p->prox = nova;   // insere após p

    return nova;
}
