#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No* prox;
} No;

typedef struct {
    No* topo;
    int tam;
} Pilha;

void inicializa(Pilha* p) {
    p->topo = NULL;
    p->tam = 0;
}

void push(Pilha* p, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if(novoNo == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória!\n");
        exit(EXIT_FAILURE);
    }
    novoNo->valor = valor;
    novoNo->prox = p->topo;
    p->topo = novoNo;
    p->tam++;
}

int pop(Pilha* p) {
    if(p->topo == NULL) {
        fprintf(stderr, "Erro: Pilha vazia!\n");
        exit(EXIT_FAILURE);
    }
    No* temp = p->topo;
    int valor = temp->valor;
    p->topo = temp->prox;
    free(temp);
    p->tam--;
    return valor;
}

void printPilha(Pilha* p) {
    if(p->tam == 0) {
        printf("\n");
        return;
    }
    
    Pilha temp;
    inicializa(&temp);
    
    // Transfere para pilha temporária (inverte a ordem)
    while(p->topo != NULL) {
        push(&temp, pop(p));
    }
    
    // Imprime e devolve para a pilha original
    while(temp.topo != NULL) {
        int val = pop(&temp);
        printf("%d", val);
        push(p, val);
        if(temp.topo != NULL) printf(" ");
    }
    printf("\n");
}

void clearPilha(Pilha* p) {
    while(p->topo != NULL) {
        pop(p);
    }
}

void add(Pilha* p) {
    if(p->tam < 2) {
        fprintf(stderr, "Erro: Elementos insuficientes para operacao!\n");
        exit(EXIT_FAILURE);
    }
    int a = pop(p);
    int b = pop(p);
    push(p, b + a); // Ordem correta: penúltimo + último
}

void sub(Pilha* p) {
    if(p->tam < 2) {
        fprintf(stderr, "Erro: Elementos insuficientes para operacao!\n");
        exit(EXIT_FAILURE);
    }
    int a = pop(p);
    int b = pop(p);
    push(p, b - a); // Ordem correta: penúltimo - último
}

void mult(Pilha* p) {
    if(p->tam < 2) {
        fprintf(stderr, "Erro: Elementos insuficientes para operacao!\n");
        exit(EXIT_FAILURE);
    }
    int a = pop(p);
    int b = pop(p);
    push(p, b * a); // Ordem correta: penúltimo * último
}

void divide(Pilha* p) {
    if(p->tam < 2) {
        fprintf(stderr, "Erro: Elementos insuficientes para operacao!\n");
        exit(EXIT_FAILURE);
    }
    int a = pop(p);
    if(a == 0) {
        fprintf(stderr, "Erro: Divisao por zero!\n");
        exit(EXIT_FAILURE);
    }
    int b = pop(p);
    push(p, b / a); // Ordem correta: penúltimo / último
}

void dup(Pilha* p) {
    if(p->tam < 1) {
        fprintf(stderr, "Erro: Pilha vazia para DUP!\n");
        exit(EXIT_FAILURE);
    }
    int a = p->topo->valor; // Não remove, apenas lê
    push(p, a);
}

void swap(Pilha* p) {
    if(p->tam < 2) {
        fprintf(stderr, "Erro: Pilha insuficiente para SWAP!\n");
        exit(EXIT_FAILURE);
    }
    int a = pop(p);
    int b = pop(p);
    push(p, a);
    push(p, b);
}

void roll(Pilha* p, int n) {
    if(n <= 0 || n > p->tam) {
        fprintf(stderr, "Erro: n fora dos limites!\n");
        exit(EXIT_FAILURE);
    }

    Pilha temp;
    inicializa(&temp);

    for(int i = 1; i < n; i++) {
        push(&temp, pop(p));
    }

    int elemento = pop(p);

    while(temp.topo != NULL) {
        push(p, pop(&temp));
    }

    push(p, elemento);
}

int main() {
    Pilha p;
    inicializa(&p);

    int N;
    if(scanf("%d", &N) != 1 || N < 1 || N > 100) {
        fprintf(stderr, "Erro: Número de comandos inválido!\n");
        return EXIT_FAILURE;
    }

    // Limpa o buffer
    int c;
    while((c = getchar()) != '\n' && c != EOF);

    for(int i = 0; i < N; i++) {
        char comando[10];
        if(scanf("%9s", comando) != 1) {
            fprintf(stderr, "Erro ao ler comando!\n");
            clearPilha(&p);
            return EXIT_FAILURE;
        }

        if(strcmp(comando, "PUSH") == 0) {
            int x;
            if(scanf("%d", &x) != 1) {
                fprintf(stderr, "Erro: Valor para PUSH inválido!\n");
                clearPilha(&p);
                return EXIT_FAILURE;
            }
            push(&p, x);
        }
        else if(strcmp(comando, "POP") == 0) pop(&p);
        else if(strcmp(comando, "ADD") == 0) add(&p);
        else if(strcmp(comando, "SUB") == 0) sub(&p);
        else if(strcmp(comando, "MULT") == 0) mult(&p);
        else if(strcmp(comando, "DIV") == 0) divide(&p);
        else if(strcmp(comando, "DUP") == 0) dup(&p);
        else if(strcmp(comando, "SWAP") == 0) swap(&p);
        else if(strcmp(comando, "ROLL") == 0) {
            int pos;
            if(scanf("%d", &pos) != 1) {
                fprintf(stderr, "Erro: Valor para ROLL inválido!\n");
                clearPilha(&p);
                return EXIT_FAILURE;
            }
            roll(&p, pos);
        }
        else if(strcmp(comando, "CLEAR") == 0) clearPilha(&p);
        else if(strcmp(comando, "PRINT") == 0) printPilha(&p);
        else {
            fprintf(stderr, "Erro: Comando desconhecido!\n");
            clearPilha(&p);
            return EXIT_FAILURE;
        }

        // Limpa o buffer
        while((c = getchar()) != '\n' && c != EOF);
    }

    clearPilha(&p);
    return EXIT_SUCCESS;
}