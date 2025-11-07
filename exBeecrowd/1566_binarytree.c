#include <stdio.h>
#include <stdlib.h>

// Função de comparação para qsort
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int NC; // número de cidades
    scanf("%d", &NC);

    while (NC--) {
        int N;
        scanf("%d", &N);
        int *alturas = (int*) malloc(N * sizeof(int));

        for (int i = 0; i < N; i++)
            scanf("%d", &alturas[i]);

        qsort(alturas, N, sizeof(int), cmp);

        for (int i = 0; i < N; i++) {
            printf("%d", alturas[i]);
            if (i < N - 1) printf(" ");
        }
        printf("\n");

        free(alturas);
    }

    return 0;
}
