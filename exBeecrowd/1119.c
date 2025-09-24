#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int id;
    struct No* prox;
    struct No* ant;   
} No;

void resolve(int n, int k, int m){
    if(n <= 0) return;

    No* inicio = (No*) malloc(sizeof(No));
    inicio->id = 1;
    No* atual = inicio;

    int i;
    for(i = 2; i <= n; i++){
        No* novo = (No*) malloc(sizeof(No));
        novo->id = i;
        atual->prox = novo;
        novo->ant = atual;
        atual = novo;
    }
    atual->prox = inicio;
    inicio->ant = atual;

    No* ptr_k = inicio;
    No* ptr_m = inicio->ant;

    int resto = n;
    int primeiro = 1;

    while(resto > 0){
        int i;
        for(i=0; i<k-1; i++){
            ptr_k = ptr_k->prox;
        }
        for(i=0; i<m-1; i++){
            ptr_m = ptr_m->ant;
        }
        if(!primeiro){
            printf(",");
        }
        primeiro = 0;

        No* selecionado_k = ptr_k;
        No* selecionado_m = ptr_m;

        if(selecionado_k == selecionado_m){
            printf("%3d", selecionado_k->id);
            ptr_k = selecionado_k->prox;
            ptr_m = selecionado_m->ant;

            selecionado_k->ant->prox = selecionado_k->prox;
            selecionado_k->prox->ant = selecionado_k->ant;
            free(selecionado_k);
            resto--;
        } else {
            printf("%3d%3d", selecionado_k->id, selecionado_m->id);
            ptr_k = selecionado_k->prox;
            ptr_m = selecionado_m->ant;

            selecionado_k->ant->prox = selecionado_k->prox;
            selecionado_k->prox->ant = selecionado_k->ant;
            
            if(ptr_k == selecionado_m){
                ptr_k = selecionado_m->prox;
            }
            if(ptr_m == selecionado_k){
                ptr_m = selecionado_k->ant;
            }

            selecionado_m->ant->prox = selecionado_m->prox;
            selecionado_m->prox->ant = selecionado_m->ant;

            free(selecionado_k);
            free(selecionado_m);
            resto -= 2;
        }
    }
    printf("\n");
}

int main(){
    int n, k, m;
    while(scanf("%d %d %d", &n, &k, &m) == 3 && (n != 0 || k != 0 || m != 0)){
        resolve(n, k, m);
    }
    return 0;
}
