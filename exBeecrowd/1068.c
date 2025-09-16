#include <stdio.h>
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
        p->itens[++(p->topo)] = item;
    }
}

char desempilha(Pilha *p) {
    if (!vazio(p)) {
        p->topo--;
    }
}

int main(){
    char expressao[MAX_TAM];

    while(scanf("%s", expressao) != EOF){

        Pilha pilha;
        inicializa(&pilha);

        int expressaoValida = 1;
        int i;
        int tam = strlen(expressao);

       for(i=0; i<tam; i++){
            if(expressao[i] == '('){
                empilha(&pilha, expressao[i]);
            } else if(expressao[i] == ')'){
                if(vazio(&pilha)){
                    expressaoValida = 0;
                    break;
                } else {
                    desempilha(&pilha);
                }
            }
        }

        if(expressaoValida && vazio(&pilha)){
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }
    return 0;
}