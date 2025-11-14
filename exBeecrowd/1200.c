#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    char chave;
    struct no *esq, *dir;
} No;

No* inserir(No *raiz, char c) {
    if (raiz == NULL) {
        No *novo = (No*) malloc(sizeof(No));
        novo->chave = c;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (c < raiz->chave)
        raiz->esq = inserir(raiz->esq, c);
    else if (c > raiz->chave)
        raiz->dir = inserir(raiz->dir, c);

    return raiz;
}

int buscar(No *raiz, char c) {
    if (raiz == NULL) return 0;
    if (raiz->chave == c) return 1;
    if (c < raiz->chave) return buscar(raiz->esq, c);
    return buscar(raiz->dir, c);
}

int primeiro;

void infixa(No *raiz) {
    if (raiz == NULL) return;
    infixa(raiz->esq);
    if (!primeiro) printf(" ");
    printf("%c", raiz->chave);
    primeiro = 0;
    infixa(raiz->dir);
}

void prefixa(No *raiz) {
    if (raiz == NULL) return;
    if (!primeiro) printf(" ");
    printf("%c", raiz->chave);
    primeiro = 0;
    prefixa(raiz->esq);
    prefixa(raiz->dir);
}

void posfixa(No *raiz) {
    if (raiz == NULL) return;
    posfixa(raiz->esq);
    posfixa(raiz->dir);
    if (!primeiro) printf(" ");
    printf("%c", raiz->chave);
    primeiro = 0;
}

int main() {
    No *raiz = NULL;
    char comando[20];
    char letra;

    while (scanf("%s", comando) != EOF) {

        if (comando[0] == 'I' && comando[1] == '\0') {
            // Comando de inserção: I c
            scanf(" %c", &letra);
            raiz = inserir(raiz, letra);
        }
        else if (comando[0] == 'P' && comando[1] == '\0') {
            // Busca: P c
            scanf(" %c", &letra);
            if (buscar(raiz, letra))
                printf("%c existe\n", letra);
            else
                printf("%c nao existe\n", letra);
        }
        else if (!strcmp(comando, "INFIXA")) {
            primeiro = 1;
            infixa(raiz);
            printf("\n");
        }
        else if (!strcmp(comando, "PREFIXA")) {
            primeiro = 1;
            prefixa(raiz);
            printf("\n");
        }
        else if (!strcmp(comando, "POSFIXA")) {
            primeiro = 1;
            posfixa(raiz);
            printf("\n");
        }
    }
    return 0;
}
