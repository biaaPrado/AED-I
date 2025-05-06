#include <stdio.h>
#include <stdlib.h>

// Definição do nó
typedef struct no {
    int info;
    struct no* prox;
} TNo, *PNo;

// Definição da fila
typedef struct fila {
    PNo ini;
    PNo fim;
} TFila, *PFila;

// Cria uma nova fila vazia
PFila cria() {
    PFila f = (PFila)malloc(sizeof(TFila));
    if (f == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

// Insere valor no fim da fila
PFila insereF(PFila f, int v) {
    PNo p = (PNo)malloc(sizeof(TNo));
    if (p == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    p->info = v;
    p->prox = NULL;

    if (f->fim == NULL) {
        f->ini = f->fim = p;
    } else {
        f->fim->prox = p;
        f->fim = p;
    }
    return f;
}

// Remove valor do início da fila
PFila removeF(PFila f, int* v) {
    if (f->ini == NULL) {
        printf("Fila vazia!\n");
        return f;
    }

    PNo p = f->ini;
    *v = p->info;
    f->ini = p->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }
    free(p);
    return f;
}

// Imprime a fila
void imprimeF(PFila f) {
    PNo p;
    for (p = f->ini; p != NULL; p = p->prox) {
        printf("%d ", p->info);
    }
    printf("\n");
}

// Libera a memória da fila
void liberaF(PFila f) {
    PNo p = f->ini;
    while (p != NULL) {
        PNo temp = p;
        p = p->prox;
        free(temp);
    }
    free(f);
}

// Separa pares e ímpares da fila original
void separa_pares_impares(PFila f, PFila* f_pares, PFila* f_impares) {
    *f_pares = cria();
    *f_impares = cria();

    int valor;
    while (f->ini != NULL) {
        f = removeF(f, &valor);
        if (valor % 2 == 0) {
            *f_pares = insereF(*f_pares, valor);
        } else {
            *f_impares = insereF(*f_impares, valor);
        }
    }
}

// Função principal para teste
int main() {
    PFila f, pares, impares;
    int i;

    f = cria();

    // Inserir elementos de 1 a 10 na fila original
    for (i = 1; i <= 10; i++) {
        f = insereF(f, i);
    }

    printf("Fila original:\n");
    imprimeF(f);

    separa_pares_impares(f, &pares, &impares);

    printf("Pares:\n");
    imprimeF(pares);

    printf("Ímpares:\n");
    imprimeF(impares);

    printf("Fila original após separação:\n");
    imprimeF(f);  // deve estar vazia

    liberaF(f);
    liberaF(pares);
    liberaF(impares);

    return 0;
}
