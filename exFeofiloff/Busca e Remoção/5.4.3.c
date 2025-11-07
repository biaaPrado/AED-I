#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int conteudo;
    struct No *ant;
    struct No *prox;
} No;

typedef struct {
    No *ini; // ponteiro para o primeiro
    No *fim; // ponteiro para o último
} fila;

// Inicializa fila vazia
void inicializaFila(fila *f) {
    f->ini = NULL;
    f->fim = NULL;
}

// Enfileira (insere no final)
void enfileira(fila *f, int x) {
    No *nova = (No *) malloc(sizeof(No));
    nova->conteudo = x;
    nova->prox = NULL;
    nova->ant = f->fim;

    if (f->fim != NULL)
        f->fim->prox = nova;
    else
        f->ini = nova; // primeiro elemento

    f->fim = nova;
}

// Desenfileira (remove do início)
int desenfileira(fila *f) {
    if (f->ini == NULL) {
        printf("Fila vazia!\n");
        return -1;
    }

    No *rem = f->ini;
    int valor = rem->conteudo;
    f->ini = rem->prox;

    if (f->ini != NULL)
        f->ini->ant = NULL;
    else
        f->fim = NULL; // fila ficou vazia

    free(rem);
    return valor;
}

// Exibe a fila
void imprimeFila(fila *f) {
    No *p = f->ini;
    while (p != NULL) {
        printf("%d ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}
