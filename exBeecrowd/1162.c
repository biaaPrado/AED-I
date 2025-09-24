#include <stdio.h>
#include <stdlib.h>

int contar_trocas(int vetor[], int tam){
    int trocas = 0, i, j;
    for(i=0; i<tam-1; i++){
        for(j=i+1; j<tam; j++){
            if(vetor[i]>vetor[j]){
                trocas++;
            }
        }
    }
    return trocas;
}

int main(){
    int num_casos;
    scanf("%d", &num_casos);

    while(num_casos > 0){
        int tam_trem, i;
        scanf("%d", &tam_trem);

        int* vagoes = (int*)malloc(tam_trem * sizeof(int));
        
        for(i=00; i<tam_trem; i++){
            scanf("%d", &vagoes[i]);
        }

        int total_trocas = contar_trocas(vagoes, tam_trem);
        printf("Optimal train swapping takes %d swaps.\n", total_trocas);
        free(vagoes);
        num_casos--;
    }
    return 0;
}