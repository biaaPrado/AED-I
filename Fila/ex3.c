#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int id;
    char mensagem[51];
    struct No* prox;
}TNo, *PNo;

typedef struct fila{
    PNo ini;
    PNo fim;
}TFila, *PFila;

PFila criaFila(){
    PFila f = (PFila)malloc(sizeof(TFila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void enqueue(PFila f, int id, char* msg){
    PNo novo = (PNo)malloc(sizeof(TNo));
    novo->id = id;
    strncpy(novo->mensagem, msg, 50);
    novo->mensagem[50] = '\0';
    novo->prox = NULL;

    if(f->fim == NULL){
        f->ini = f->fim = novo;
    }else{
        f->fim->prox = novo;
        f->fim = novo;
    }
}

void dequeue(PFila f){
    if(f->ini == NULL){
        printf("Fila vazia!\n");
        exit(0);
    }

    PNo temp = f->ini;
    f->ini = f->ini->prox;
    if(f->ini == NULL)
        f->fim = NULL;

    free(temp);
}

void printFila(PFila f){
    if(f->ini == NULL){
        printf("\n");
        return;
    }

    PNo atual = f->ini;
    while(atual != NULL){
        printf("ID: %d - %s\n", atual->id, atual->mensagem);
        atual = atual->prox;
    }
}

void clearFila(PFila f){
    while(f->ini != NULL){
        dequeue(f);
    }
}

void liberaFila(PFila f){
    clearFila(f);
    free(f);
}

int main(){
    int n;
    PFila fila = criaFila();

    scanf("%d", &n);
    while (n <= 0 || n > 10) {
        scanf("%d", &n);
    }
    getchar();

    char linha[100], comando[10];
    int num, i;

    for(i=0; i<n; i++){
        fgets(linha, sizeof(linha), stdin);
        sscanf(linha, "%s %d", comando, &num);

        if(strcmp(comando, "ENQUEUE") == 0){
            char msg[51];
            char* ptr = strchr(linha, ' ');
            if (ptr != NULL) ptr = strchr(ptr + 1, ' ');
            if (ptr != NULL) {
            strncpy(msg, ptr + 1, 50);
            msg[50] = '\0';
            msg[strcspn(msg, "\n")] = '\0';
            enqueue(fila, num, msg);
        }
        }else if(strcmp(comando, "DEQUEUE") == 0){
            dequeue(fila);
        }else if(strcmp(comando, "PRINT") == 0){
            printFila(fila);
        }else if(strcmp(comando, "CLEAR") == 0){
            clearFila(fila);
        }
    }

    liberaFila(fila);
    return 0;
}