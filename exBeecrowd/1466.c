#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *esquerda;
    struct Node *direita;
} Node;

Node* criar_no(int valor) {
    Node *novo_no = (Node *)malloc(sizeof(Node));
    novo_no->valor = valor;
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    return novo_no;
}

Node* inserir(Node *raiz, int valor) {
    if (raiz == NULL) {
        return criar_no(valor);
    }
    
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } 
    else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    
    return raiz;
}

void percurso_por_nivel(Node *raiz) {
    if (raiz == NULL) {
        return;
    }

    Node* fila[501];
    int inicio = 0;
    int fim = 0;

    fila[fim++] = raiz;
    
    int primeiro_item = 1;

    while (inicio < fim) {
        
        Node *atual = fila[inicio++];

        if (primeiro_item) {
            printf("%d", atual->valor);
            primeiro_item = 0;
        } else {
            printf(" %d", atual->valor);
        }

        if (atual->esquerda != NULL) {
            fila[fim++] = atual->esquerda;
        }
        if (atual->direita != NULL) {
            fila[fim++] = atual->direita;
        }
    }
}

void liberar_arvore(Node *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberar_arvore(raiz->esquerda);
    liberar_arvore(raiz->direita);
    free(raiz);
}

int main() {
    int C, N, valor;
    int caso_num = 1;

    scanf("%d", &C);

    while (C--) {
        Node *raiz = NULL;
        
        scanf("%d", &N);
        
        for (int i = 0; i < N; i++) {
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }

        printf("Case %d:\n", caso_num++);
        percurso_por_nivel(raiz);
        printf("\n\n");
        
        liberar_arvore(raiz);
    }

    return 0;
}