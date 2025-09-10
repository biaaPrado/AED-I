#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int X[N];  // vetor estático (sem malloc)

    // leitura usando ponteiros
    for (int i = 0; i < N; i++) {
        scanf("%d", (X + i));  // X+i é o endereço de X[i]
    }

    int menor_valor = *X;  // primeiro elemento do vetor
    int posicao = 0;

    // percorre o vetor com ponteiros
    for (int i = 1; i < N; i++) {
        if (*(X + i) < menor_valor) {
            menor_valor = *(X + i);
            posicao = i;
        }
    }

    printf("Menor valor: %d\n", menor_valor);
    printf("Posicao: %d\n", posicao);

    return 0;
}
