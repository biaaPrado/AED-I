#include <stdio.h>
#define MAX_pilha 100

typedef struct{
    char vet[MAX_pilha];
    int topo;
}tpilha;

tpilha* nova(){
    tpilha *p = (tpilha*)malloc(sizeof(tpilha));
    if(p!=NULL){
        p->topo = -1;
    }
    return p;
}

void push(tpilha *p, char c){
    if(p->topo < MAX_pilha-1){
        p->topo++;
        p->vet[p->topo] = c;
    }
}

char pop(tpilha *p){
    if(p->topo >= 0){
        return p->vet[p->topo--];
    }
    return '\0';
}

void imprimir(tpilha *p){
    int i;
    if(p->topo < 0){
        printf("Pilha vazia");
        return; 
    }
    for (i=p->topo; i>=0; i--)
        printf("%c", p->vet[i]);
    printf("\n");
}

int main(){
    tpilha *pilha;
    char str[MAX_pilha];
    int i;
    char c;

    printf("Digite uma frase: ");
    fgets(str, MAX_pilha, stdin);
    
    pilha = nova();
    for (i=0; str[i]!='\0' && str[i] != '\n'; i++){
        push(pilha, str[i]);
    }
    for (i=pilha->topo; i<=0; i++){
       c = pop(pilha);
        printf("%c", c);
    }
    printf("\n");
    free(pilha);
    return 0;
}