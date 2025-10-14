#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define MAX_EXPRESSION_LEN 1001

typedef struct No {
    char item;
    struct No* proximo;
} No;

typedef struct {
    No* topo; 
} Pilha;


void inicializa(Pilha *p) {
    p->topo = NULL;
}

int vazio(Pilha *p) {
    return p->topo == NULL;
}

void empilha(Pilha *p, char item) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        return;
    }
    novoNo->item = item;
    novoNo->proximo = p->topo; // O novo nó aponta para o antigo topo
    p->topo = novoNo;        // O topo da pilha agora é o novo nó
}

void desempilha(Pilha *p) {
    if (!vazio(p)) {
        No* temp = p->topo;      // Guarda o nó a ser removido
        p->topo = p->topo->proximo; // Atualiza o topo para o próximo elemento
        free(temp);              // Libera a memória do nó removido
    }
}

void libera_pilha(Pilha *p) {
    while (!vazio(p)) {
        desempilha(p);
    }
}

int main() {
    int N;
    char expressao[MAX_EXPRESSION_LEN];

    scanf("%d", &N);
    getchar(); 

    while (N > 0) {
        fgets(expressao, MAX_EXPRESSION_LEN, stdin);
        expressao[strcspn(expressao, "\n")] = 0;

        Pilha pilha;
        inicializa(&pilha);

        int expressaoValida = 1;
        int tam = strlen(expressao);

        for (int i = 0; i < tam; i++) {
            if (expressao[i] == '(') {
                empilha(&pilha, expressao[i]);
            } else if (expressao[i] == ')') {
                if (vazio(&pilha)) {
                    expressaoValida = 0;
                    break;
                } else {
                    desempilha(&pilha);
                }
            }
        }

        if (expressaoValida && vazio(&pilha)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }

        libera_pilha(&pilha);

        N--;
    }

    return 0;
}