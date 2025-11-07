#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *esq, *dir;
} No;

No* inserir(No *raiz, int x) {
    if (raiz == NULL) {
        No *novo = (No*) malloc(sizeof(No));
        novo->valor = x;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (x < raiz->valor)
        raiz->esq = inserir(raiz->esq, x);
    else
        raiz->dir = inserir(raiz->dir, x);

    return raiz;
}

void preOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("%d", raiz->valor);
        if (raiz->esq != NULL || raiz->dir != NULL) printf(" ");
        if (raiz->esq) {
            preOrdem(raiz->esq);
            if (raiz->dir) printf(" ");
        }
        if (raiz->dir) preOrdem(raiz->dir);
    }
}

void inOrdem(No *raiz) {
    if (raiz != NULL) {
        inOrdem(raiz->esq);
        printf("%d", raiz->valor);
        if (raiz->dir != NULL) printf(" ");
        inOrdem(raiz->dir);
    }
}

void posOrdem(No *raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d", raiz->valor);
        if (!(raiz->esq == NULL && raiz->dir == NULL)) printf(" ");
    }
}

void liberaArvore(No *raiz) {
    if (raiz == NULL) return;
    liberaArvore(raiz->esq);
    liberaArvore(raiz->dir);
    free(raiz);
}

int main() {
    int C; // número de casos
    scanf("%d", &C);

    for (int caso = 1; caso <= C; caso++) {
        int N, x;
        No *raiz = NULL;

        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &x);
            raiz = inserir(raiz, x);
        }

        printf("Case %d:\n", caso);
        printf("Pre.:");
        void imprimePre(No *r) {
            if (r) {
                printf(" %d", r->valor);
                imprimePre(r->esq);
                imprimePre(r->dir);
            }
        }
        imprimePre(raiz);
        printf("\n");

        printf("In..:");
        void imprimeIn(No *r) {
            if (r) {
                imprimeIn(r->esq);
                printf(" %d", r->valor);
                imprimeIn(r->dir);
            }
        }
        imprimeIn(raiz);
        printf("\n");

        printf("Post:");
        void imprimePost(No *r) {
            if (r) {
                imprimePost(r->esq);
                imprimePost(r->dir);
                printf(" %d", r->valor);
            }
        }
        imprimePost(raiz);
        printf("\n\n");

        liberaArvore(raiz);
    }

    return 0;
}
