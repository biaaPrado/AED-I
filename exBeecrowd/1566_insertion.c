#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int NC, N;
    scanf("%d", &NC);
    while (NC--) {
        scanf("%d", &N);
        int i;
        int alturas[N];
        for (i = 0; i < N; i++) {
            scanf("%d", &alturas[i]);
        }
        qsort(alturas, N, sizeof(int), compare);
        for (i = 0; i < N; i++) {
            if (i) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");
    }
    return 0;
}
