#include <stdio.h>
#include <string.h> 

#define MAX_TAM 1001

typedef struct {
    char itens[MAX_TAM];
    int topo;
} Pilha;

void inicializa(Pilha *p) {
    p->topo = -1;
}

int vazio(Pilha *p) {
    return p->topo == -1;
}

void empilha(Pilha *p, char item) {
    if (p->topo < MAX_TAM - 1) {
        p->topo++; // Incrementa o topo PRIMEIRO
        p->itens[p->topo] = item; // DEPOIS insere o item
    }
}

void desempilha(Pilha *p) {
    if (!vazio(p)) {
        p->topo--;
    }
}

int main() {
    int N;
    char expressao[MAX_TAM];

    scanf("%d", &N);
    getchar();

    while (N > 0) {
        fgets(expressao, MAX_TAM, stdin);
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

        N--; 
    }

    return 0;
}