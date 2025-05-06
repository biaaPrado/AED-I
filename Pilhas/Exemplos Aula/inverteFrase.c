#include <stdio.h>
#define MAX_pilha 100

void imprimir(tpilha *p){
    int i;
    if(p->topo < 0){
        printf("Pilha vazia");
        return; 
    }
    for (i=p->topo; i>=0; i--)
        printf("%d", p->vet[i]);
}

typedef struct{
    char vet[MAX_pilha];
    int topo;
}tpilha;

int main(){
    tpilha *pilha;
    char str[MAX_pilha];
    int i;
    printf("Digite uma frase: ");
    gets(str);
    pilha = nova();
    for (i=0; str[i]!='\n'; i++){
        push(pilha, str[i]);
    }
    for (i=pilha->topo; i<=0; i++){
        Pop(pilha, *C);
        printf("%c", C);
    }
    free(pilha);
    return 0;
}