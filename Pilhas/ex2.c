#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct No{
    int valor;
    struct No* prox;
}No;
 
typedef struct{
    No* topo;
    int tam;
}Pilha;
 
void inicializa(Pilha* p){
    p->topo = NULL;
    p->tam = 0;
}
 
void push(Pilha* p, int valor){
    No* novoNo = (No*)malloc(sizeof(No));
    if(novoNo == NULL){
        exit(1);
    }
    novoNo->valor = valor;
    novoNo->prox = p->topo;
    p->topo = novoNo;
    p->tam++;
}
 
int pop(Pilha* p){
    if(p->topo == NULL){
        printf("Erro: Pilha vazia!\n");
        exit(0);
    }
    No* temp = p->topo;
    int valor = temp->valor;
    p->topo = temp->prox;
    free(temp);
    p->tam--;
    return valor;
}
 
void printPilha(Pilha* p){
    if(p->tam == 0){
        printf("\n");
        return;
    }
    
    No* atual = p->topo;
    int* valores = malloc(p->tam * sizeof(int));
    if(valores == NULL){
        exit(1);
    }
 
    int i = 0;
    while(atual != NULL){
        valores[i++] = atual->valor;
        atual = atual->prox;
    }
 
    int j=0;
    for(j=0; j<p->tam; j++){
        printf("%d", valores[j]);
        if(j<p->tam-1)
            printf(" ");
    }
    printf("\n");
    free(valores);
}
 
void clearPilha(Pilha* p){
    while(p->topo != NULL){
        pop(p);
    }
}
 
void add(Pilha* p){
    if(p->tam < 2){
        printf("Erro: Faltam elementos na pilha!\n");
        exit(0);
    }
    int a = pop(p);
    int b = pop(p);
    push(p, b + a);
}
 
void sub(Pilha* p){
    if(p->tam < 2){
        printf("Erro: Faltam elementos na pilha!\n");        
        exit(0);
    }
    int a = pop(p);
    int b = pop(p);
    push(p, b - a);
}
 
void mult(Pilha* p){
    if(p->tam < 2){
        printf("Erro: Faltam elementos na pilha!\n");
        exit(0);
    }
    int a = pop(p);
    int b = pop(p);
    push(p, b * a);
}
 
void divisao(Pilha* p){
    if(p->tam < 2){
        printf("Erro: Faltam elementos na pilha!\n");
        exit(EXIT_FAILURE);
    }
    int a = pop(p);
    if(a == 0){
        printf("Erro: Divisao por zero!\n");
        exit(0);
    }
    int b = pop(p);
    push(p, b / a);
}
 
void dup(Pilha* p){
    if(p->tam < 1){
        printf("Erro: Pilha vazia para DUP!\n");
        exit(0);
    }
    int a = p->topo->valor;
    push(p, a);
}
 
void swap(Pilha* p){
    if(p->tam < 2){
        printf("Erro: Pilha insuficiente para SWAP!\n");
        exit(0);
    }
    int a = pop(p);
    int b = pop(p);
    push(p, a);
    push(p, b);
}
 
void roll(Pilha* p, int n){
    if(n <= 0 || n > p->tam){
        printf("Erro: Posicao invalida!\n");
        exit(0);
    }
 
    Pilha aux;
    inicializa(&aux);
 
    int i;
    for (i = 0; i < n-1; i++) {
        push(&aux, pop(p));
    }
 
    int elemento_n = pop(p); // o n-ésimo elemento
    while (aux.tam > 0) {
        push(p, pop(&aux));
    }
    push(p, elemento_n);
}
 
 
int main(){
    Pilha p;
    inicializa(&p);
 
    int N, ch;
    if (scanf("%d", &N) != 1 || N < 1 || N > 100) {
        printf("Erro: n fora dos limites!\n");
        return 0;
    }
 
    do { ch = getchar(); } while (ch != '\n' && ch != EOF);
 
    int i;
    for (i=0; i<N; i++){
        char comando[10];
        if(scanf("%9s", comando) != 1) {
            return 1;
        }
        
        if(strcmp(comando, "PUSH") == 0){
            int x;
            if(scanf("%d", &x) != 1) {
                return 1;
            }
            push(&p, x);
        }
        else if(strcmp(comando, "POP") == 0){pop(&p);}
        else if(strcmp(comando, "ADD") == 0){add(&p);}        
        else if(strcmp(comando, "SUB") == 0){sub(&p);}
        else if(strcmp(comando, "MUL") == 0){mult(&p);}
        else if(strcmp(comando, "DIV") == 0){divisao(&p);}
        else if(strcmp(comando, "DUP") == 0){dup(&p);}
        else if(strcmp(comando, "SWAP") == 0){swap(&p);}
        else if(strcmp(comando, "ROLL") == 0){
            int pos; 
            if(scanf("%d", &pos) != 1){
                return 1;
            }
            roll(&p, pos);
        }
        else if(strcmp(comando, "CLEAR") == 0){clearPilha(&p);}
        else if(strcmp(comando, "PRINT") == 0){printPilha(&p);}
 
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
    } 
 
    return 0;
}