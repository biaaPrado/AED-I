#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

char desempilha(Pilha *p) {
    if (!vazio(p)) {
        return p->itens[p->topo--];
    }
    return  '\0'; 
}

char verTopo(Pilha *p) {
    if (!vazio(p)) {
        return p->itens[p->topo];
    }
    return '\0'; // Retorna caractere nulo se a pilha estiver vazia
}

int precedencia(char operador) {
    switch (operador) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

int main(){
    int N;
    scanf("%d", &N);
    getchar();

    while(N--){
        char infixa[MAX_TAM];
        scanf("%s", infixa);

        Pilha pilha_operadores;
        inicializa(&pilha_operadores);

        int i;
        int tam = strlen(infixa);

        for(i = 0; i < tam; i++){
            char token = infixa[i];

            if(isalnum(token)){ // Se for operando (número ou letra)
                printf("%c", token);
            } else if(token == '('){
                empilha(&pilha_operadores, token);
            } else if(token == ')'){
                while(!vazio(&pilha_operadores) && verTopo(&pilha_operadores) != '('){
                    printf("%c", verTopo(&pilha_operadores));
                    desempilha(&pilha_operadores);
                }
                desempilha(&pilha_operadores); // Remove o '(' da pilha
            } else { // Se for operador
                while(!vazio(&pilha_operadores) && 
                        precedencia(verTopo(&pilha_operadores)) >= precedencia(token)){
                    printf("%c", desempilha(&pilha_operadores));
                }
                empilha(&pilha_operadores, token);
            }
        }
        while (!vazio(&pilha_operadores)){
            printf("%c", desempilha(&pilha_operadores));
        }
        printf("\n");
    }
    return 0;
}