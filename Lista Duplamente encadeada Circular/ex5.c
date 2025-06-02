#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int codigo;
    char descricao[51];
    struct No* prox;
    struct No* ant;
}No;

typedef struct Lista{
    No* ini;
}Lista;

Lista* criaLista(){
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->ini = NULL;
    return lista;
}

No* busca(Lista* lista, int codigo){
    if(lista->ini == NULL)
        return NULL;
    
    No* p = lista->ini;
    do{
        if(p->codigo == codigo)
            return p;
        p = p->prox;
    }while(p != lista->ini);

    return NULL;
}

void add(Lista* lista, int codigo, char* descricao){
    if(busca(lista, codigo) != NULL){
        printf("Codigo ja existente!\n");
        return;
    }

    No* novo = (No*)malloc(sizeof(No));
    novo->codigo = codigo;
    strcpy(novo->descricao, descricao);

    if(lista->ini == NULL){
        novo->prox = novo;
        novo->ant = novo;
        lista->ini = novo;
    }else{
        No* ult = lista->ini->ant;
        ult->prox = novo;
        novo->ant = ult;
        novo->prox = lista->ini;
        lista->ini->ant = novo;   
    }
}

void removeCodigo(Lista* lista, int codigo){
    No* p = busca(lista,codigo);
    if(p == NULL){
        printf("Codigo nao encontrado!\n");
        return;
    }

    if(p->prox == p){
        free(p);
        lista->ini = NULL;
        return;
    }

    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    if(lista->ini == p)
        lista->ini = p->prox;
    free(p);
}

void printForward(Lista *lista){
    if(lista->ini == NULL){
        printf("Lista vazia!\n");
        return;
    }

    No* p = lista->ini;
    do{
        printf("Codigo: %d - %s\n", p->codigo, p->descricao);
        p = p->prox;
    }while(p != lista->ini);
}

void printReverse(Lista* lista){
    if(lista->ini == NULL){
        printf("Lista vazia!\n");
        return;
    }

    No* p = lista->ini->ant;
    No* fim = p;

    do{
        printf("Codigo: %d - %s\n", p->codigo, p->descricao);
        p = p->ant;
    }while(p != fim);
}

void search(Lista* lista, int codigo){
    No*p = busca(lista, codigo);
    if(p == NULL){
        printf("Codigo nao encontrado!\n");
    }else{
        printf("Codigo: %d - %s\n", p->codigo, p->descricao);
    }
}

void libera(Lista* lista){
    if(lista->ini == NULL){
        free(lista);
        return;
    }

    No* atual = lista->ini->prox;
    while(atual != lista->ini){
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista->ini);
    free(lista);
}

int main(){
    int N, codigo, count = 0;
    Lista* lista = criaLista();
    char linha[100], desc[51];

    scanf("%d", &N);
    if(N < 1 || N > 100){
        printf("N nao e valido!");
        libera(lista);
        return 0;
    }
    getchar();

    while(fgets(linha, sizeof(linha), stdin) != NULL){
        linha[strcspn(linha, "\n")] = '\0';

        if(strncmp(linha, "ADD", 3) == 0){
            sscanf(linha+4, "%d %[^\n]", &codigo, desc);
            add(lista, codigo, desc);
        }
        else if(strncmp(linha, "REMOVE", 6) == 0){
            sscanf(linha+7, "%d", &codigo);
            removeCodigo(lista, codigo);
        }
        else if(strcmp(linha, "PRINT_FORWARD") == 0){
            printForward(lista);
        }
        else if(strcmp(linha, "PRINT_REVERSE") == 0){
            printReverse(lista);
        }
        else if(strncmp(linha, "SEARCH", 6) == 0){
            sscanf(linha+7, "%d", &codigo);
            search(lista, codigo);
        }

        count++;
        if(count == N)
            break;
    }

    if(count < N)
        printf("N superior ao numero de comandos!\n");

    libera(lista);
    return 0;
}
