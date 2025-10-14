#include <stdio.h>
#include <stdlib.h> 

int main() {
    int N;
    scanf("%d", &N);

    int *vetor = (int *) malloc(N * sizeof(int));

    if (vetor == NULL) {
        return 1;
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &vetor[i]);
    }

    int menor_valor = vetor[0];
    int posicao = 0;

    for (int i = 1; i < N; i++) {
        if (vetor[i] < menor_valor) {
            menor_valor = vetor[i];
            posicao = i;
        }
    }

    printf("Menor valor: %d\n", menor_valor);
    printf("Posicao: %d\n", posicao);

    free(vetor);

    return 0;
}