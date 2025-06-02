#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int info;
    struct No* prox;
}No; 

typedef struct Pilha{
    char nome[51];
    No* topo;
    struct Pilha *prox;
}Pilha; 

Pilha *PLista = NULL;

No* criaNo(int info){
    No *novo = (No*)malloc(sizeof(No));
    novo->info = info;
    novo->prox = NULL;
    return novo;
}

Pilha* criaPilha(char *nome){
    Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
    strcpy(novo->nome, nome);
    novo->topo = NULL;
    novo->prox = PLista;
    PLista = novo;
    return novo;
}

Pilha* buscaPilha(char *nome){
    Pilha *atual = PLista;
    while(atual != NULL){
        if(strcmp(atual->nome, nome) == 0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void liberaNo(No *topo){
    while(topo != NULL){
        No *temp = topo;
        topo = topo->prox;
        free(temp);
    }
}

void removePilha(char *nome){
    Pilha *atual = PLista;
    Pilha *ant = NULL;

    while (atual != NULL){
        if(strcmp(atual->nome, nome) == 0){
            if(ant == NULL)
                PLista = atual->prox;
            else
                ant->prox = atual->prox;
            liberaNo(atual->topo);
            free(atual);
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
}

void liberaPilha(){
    Pilha *atual = PLista;
    while (atual != NULL){
        Pilha *temp = atual;
        atual = atual->prox;
        liberaNo(temp->topo);
        free(temp);
    }
    PLista = NULL;    
}

void init(char *nome){
    if(buscaPilha(nome) == NULL)
        criaPilha(nome);
}

void push(char *nome, int valor){
    Pilha *pilha = buscaPilha(nome);
    if(pilha == NULL){
        printf("Pilha %s nao encontrada!\n", nome);
        exit(1);
    }
    No *novo = criaNo(valor);
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

void pop(char *nome){
    Pilha *pilha = buscaPilha(nome);
    if(pilha == NULL){
        printf("Pilha %s nao encontrada!\n", nome);
        exit(1);
    }
    if(pilha->topo == NULL){
        printf("Pilha %s vazia!\n", nome);
        exit(1);
    }
    No *temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(temp);

    if(pilha->topo == NULL)
        removePilha(nome);
}

void top(char *nome){
    Pilha *pilha = buscaPilha(nome);
    if(pilha == NULL){
        printf("Pilha %s nao encontrada!\n", nome);
        exit(1);
    }
    if(pilha->topo == NULL){
        printf("Pilha %s vazia!\n", nome);
        exit(1);
    }
    printf("%d\n", pilha->topo->info);
}

void print(char *nome){
    Pilha *pilha = buscaPilha(nome);
    if(pilha == NULL){
        printf("Pilha %s nao encontrada!\n", nome);
        exit(1);
    }

    printf("[");
    No *atual = pilha->topo;
    int ini = 1;
    while(atual != NULL){
        if(!ini){
            printf(", ");
        }
        printf("%d", atual->info);
        ini = 0;
        atual = atual->prox;
    }
    printf("]\n");
}

void merge(char *nomeA, char *nomeB){
    if(strcmp(nomeA, nomeB) == 0) {
        printf("Erro: pilhas iguais!\n");
        exit(1);
    }

    Pilha *pilhaA = buscaPilha(nomeA);
    Pilha *pilhaB = buscaPilha(nomeB);

    if(pilhaA == NULL || pilhaB == NULL){
        printf("Erro: pilhas nao encontradas!\n");
        exit(1);
    }

    if(pilhaB->topo != NULL){
        No *ultB = pilhaB->topo;
        while(ultB != NULL && ultB->prox != NULL){
            ultB = ultB->prox;
        }
        
        if(ultB != NULL){
            ultB->prox = pilhaA->topo;
            pilhaA->topo = pilhaB->topo;
        }
        pilhaB->topo = NULL;
    }
    removePilha(nomeB);
}

void split(char *nome, char *novoNome, int k){
    Pilha *pilha = buscaPilha(nome);
    if(pilha == NULL){
        printf("Pilha %s nao encontrada!\n", nome);
        exit(1);
    }

    if(pilha->topo == NULL) {
        printf("Pilha %s vazia!\n", nome);
        exit(1);
    }

    if(buscaPilha(novoNome) != NULL) {
        printf("Pilha %s ja existe!\n", novoNome);
        exit(1);
    }

    No *atual = pilha->topo;
    int tam = 0;
    while(atual != NULL) {
        tam++;
        atual = atual->prox;
    }

    if(k <= 0 || k > tam) {
        k = tam;
    }

    Pilha *novo = criaPilha(novoNome);
    No *topoOriginal = NULL;

    int i;
    for(i=0; i< k && pilha->topo != NULL; i++){
        No *temp = pilha->topo;
        pilha->topo = temp->prox;

        temp->prox = topoOriginal;
        topoOriginal = temp;
    }

    while(topoOriginal != NULL){
        No *temp = topoOriginal;
        topoOriginal = topoOriginal->prox;

        temp->prox = novo->topo;
        novo->topo = temp;
    }

    if(pilha->topo == NULL){
        removePilha(nome);
    }
}

void show(){
    if(PLista == NULL){
        printf("\n");
        return; 
    }

    Pilha *atual = PLista;
    while(atual != NULL){
        printf("%s: [", atual->nome);
        No *no = atual->topo;
        int ini = 1;
        while(no != NULL){
            if(!ini)
                printf(", ");
            printf("%d", no->info);
            ini = 0;
            no = no->prox;
        }
        printf("]\n");
        atual = atual->prox;   
    }
}


int main(){
    int n;
    char linha[100], comando[30], nome[51], nomeA[51], nomeB[51], novoNome[30];
    int valor, k, i;

    do{
        scanf("%d", &n);
        getchar();
    }while (n < 1 || n > 100);


    for(i=0; i < n; i++){
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = '\0';

        if(strstr(linha, ":INIT")){
            sscanf(linha, "%[^:]:INIT", nome);
            init(nome);
        }
        else if(strstr(linha, ":PUSH")){
            sscanf(linha, "%[^:]:PUSH %d", nome, &valor);
            push(nome, valor);
        }
        else if(strstr(linha, ":POP")){
            sscanf(linha, "%[^:]:POP", nome);
            pop(nome);
        }
        else if(strstr(linha, ":TOP")){
            sscanf(linha, "%[^:]:TOP", nome);
            top(nome);
        }
        else if(strstr(linha, ":PRINT")){
            sscanf(linha, "%[^:]:PRINT", nome);
            print(nome);
        }
        else if(strncmp(linha, "MERGE", 5) == 0 ){
            sscanf(linha, "MERGE %s %s", nomeA, nomeB);
            merge(nomeA, nomeB);
        }
        else if(strncmp(linha, "SPLIT", 5) == 0 ){
            if(sscanf(linha, "SPLIT %s %s %d", nomeA, novoNome, &k) == 3){ 
                split(nomeA, novoNome, k);
            }else{
                exit(1);
            }
        }
        else if(strcmp(linha, "SHOW") == 0){
            show();
        }
    }
    liberaPilha();
    return 0;
}