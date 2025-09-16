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
        p->topo++;
        p->itens[p->topo] = item;
    }
}

void desempilha(Pilha *p) {
    if (!vazio(p)) {
        p->topo--;
    }
}


int main(){
    int N;
    scanf("%d", &N);

    while(N--){
        char mina[MAX_TAM];
        scanf("%s", mina);

        int diamantes_extraidos = 0;
    
        Pilha pilha;
        inicializa(&pilha);

        int i;
        int tamanho_string = strlen(mina);

        for(i = 0; i < tamanho_string; i++){
            if(mina[i] == '<'){
                empilha(&pilha, mina[i]);
            } else if(mina[i] == '>'){
                if(!vazio(&pilha)){
                    diamantes_extraidos++;
                    desempilha(&pilha);
                }
            }
        }
        
        printf("%d\n", diamantes_extraidos);
    }
    return 0;
}