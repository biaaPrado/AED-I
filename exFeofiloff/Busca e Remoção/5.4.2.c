#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
    int conteudo;
    struct celula *seg;
} celula;

// Inicializa a fila circular com célula-cabeça
celula *inicializaFila() {
    celula *cabeca = (celula *) malloc(sizeof(celula));
    cabeca->seg = cabeca; // circular
    return cabeca;
}

// Enfileirar (inserir no final)
void enfileira(int x, celula *f) {
    celula *nova = (celula *) malloc(sizeof(celula));
    nova->conteudo = x;
    nova->seg = f->seg;   // aponta para o primeiro
    f->seg = nova;        // último aponta para nova
    f = nova;             // atualiza ponteiro do fim
}

// Desenfileirar (remover o primeiro)
int desenfileira(celula *f) {
    celula *cabeca = f;
    celula *primeiro = cabeca->seg;

    if (primeiro == cabeca) {
        printf("Fila vazia!\n");
        return -1;
    }

    int valor = primeiro->conteudo;
    cabeca->seg = primeiro->seg;
    free(primeiro);
    return valor;
}

// Exibir fila
void imprimeFila(celula *f) {
    celula *p = f->seg;
    while (p != f) {
        printf("%d ", p->conteudo);
        p = p->seg;
    }
    printf("\n");
}
