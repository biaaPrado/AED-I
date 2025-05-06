#include <stdio.h>
#include <stdlib.h>

// Definição do nó da fila
typedef struct no {
    int info;
    struct no* prox;
} TNo, *PNo;

// Definição da estrutura da fila
typedef struct fila {
    PNo ini;
    PNo fim;
} TFila, *PFila;

// Cria fila vazia
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

// Insere no final
PFila insereF(PFila f, int v) {
    PNo p = (PNo)malloc(sizeof(TNo));
    if (p == NULL) {
        printf("Erro de alocação!\n");
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

// Remove do início
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
    if (f->ini == NULL) {
        printf("Fila vazia!\n");
        return;
    }
    for (p = f->ini; p != NULL; p = p->prox) {
        printf("%d ", p->info);
    }
    printf("\n");
}

// Libera a fila
void liberaF(PFila f) {
    PNo p = f->ini;
    while (p != NULL) {
        PNo temp = p;
        p = p->prox;
        free(temp);
    }
    free(f);
}

// Menu interativo
int main() {
    PFila fila = cria();
    int opcao, valor;

    do {
        printf("\n--- Menu da Fila ---\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Imprimir\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite um valor para inserir: ");
                scanf("%d", &valor);
                fila = insereF(fila, valor);
                break;
            case 2:
                fila = removeF(fila, &valor);
                if (fila->ini != NULL || fila->fim != NULL) {
                    printf("Valor removido: %d\n", valor);
                }
                break;
            case 3:
                printf("Fila atual: ");
                imprimeF(fila);
                break;
            case 4:
                liberaF(fila);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 4);

    return 0;
}
