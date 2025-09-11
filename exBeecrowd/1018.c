#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    printf("%d\n", N);

    int notas[] = {100, 50, 20, 10, 5, 2, 1};
    int qtd, i;

    for(i = 0; i < 7; i++) {
        qtd = N / notas[i];   // quantidade de notas
        printf("%d nota(s) de R$ %d,00\n", qtd, notas[i]);
        N = N % notas[i];     // atualiza o valor restante
    }

    return 0;
}
