#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FITA_LEN 302

typedef struct No {
    char base;
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

void empilha(Pilha *p, char base) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) return; 

    novoNo->base = base;
    novoNo->proximo = p->topo; // O novo nó aponta para o antigo topo

    p->topo = novoNo;
}

void desempilha(Pilha *p) {
    if (!vazio(p)) {
        No* temp = p->topo;         // Guarda o endereço do topo atual
        p->topo = p->topo->proximo; // Atualiza o topo para o próximo
        free(temp);                 // 2. Libera a memória do nó removido
    }
}

char ver_topo(Pilha *p) {
    if (!vazio(p)) {
        return p->topo->base;
    }
    return '\0'; 
}

void libera_pilha(Pilha *p) {
    while (!vazio(p)) {
        desempilha(p);
    }
}

int sao_par(char b1, char b2) {
    return (b1 == 'B' && b2 == 'S') || (b1 == 'S' && b2 == 'B') ||
           (b1 == 'C' && b2 == 'F') || (b1 == 'F' && b2 == 'C');
}

int main() {
    char fita_rnaa[MAX_FITA_LEN];

    while (scanf("%s", fita_rnaa) != EOF) {
        int ligacoes = 0;
        Pilha pilha;
        inicializa(&pilha);

        int tamanho = strlen(fita_rnaa);

        for (int i = 0; i < tamanho; i++) {
            char base_atual = fita_rnaa[i];

            if (vazio(&pilha)) {
                empilha(&pilha, base_atual);
            } else {
                if (sao_par(base_atual, ver_topo(&pilha))) {
                    ligacoes++;
                    desempilha(&pilha);
                } else {
                    empilha(&pilha, base_atual);
                }
            }
        }

        printf("%d\n", ligacoes);

        libera_pilha(&pilha);
    }

    return 0;
}