#include <stdio.h>

int main() {
    int NC;  // número de cidades
    scanf("%d", &NC);

    while(NC--) {
        int N;
        scanf("%d", &N);
        int alturas[N];

        int i, j;  // declarando i e j fora dos for
        for(i = 0; i < N; i++) {
            scanf("%d", &alturas[i]);
        }

        // Selection Sort
        int min_idx, temp;
        for(i = 0; i < N - 1; i++) {
            min_idx = i;
            for(j = i + 1; j < N; j++) {
                if(alturas[j] < alturas[min_idx]) {
                    min_idx = j;
                }
            }
            // Troca
            temp = alturas[i];
            alturas[i] = alturas[min_idx];
            alturas[min_idx] = temp;
        }

        // Imprimir vetor ordenado
        for(i = 0; i < N; i++) {
            if(i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");
    }

    return 0;
}
