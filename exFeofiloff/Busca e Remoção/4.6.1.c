//4.6.2 Escreva uma versão da função BuscaEInsere para listas encadeadas sem cabeça.

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da célula (nó da lista)
typedef struct No {
    int conteudo;
    struct No *prox;
} No;

// Função que busca e remove o primeiro nó que contém x
void BuscaERemove(int x, No **lista) {
    No *p, *q;

    // Caso a lista esteja vazia
    if (*lista == NULL)
        return;

    // Caso especial: o primeiro nó contém o valor procurado
    if ((*lista)->conteudo == x) {
        q = *lista;
        *lista = (*lista)->prox;  // Atualiza o início da lista
        free(q);
        return;
    }

    // Caso geral: procura o valor nas próximas células
    p = *lista;
    q = p->prox;

    while (q != NULL && q->conteudo != x) {
        p = q;
        q = q->prox;
    }

    // Se encontrou o valor, remove o nó
    if (q != NULL) {
        p->prox = q->prox;
        free(q);
    }
}
