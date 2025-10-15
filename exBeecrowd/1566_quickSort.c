#include <stdio.h>
#include <stdlib.h>

// Função para particionar o vetor
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int j, temp;

    for(j = low; j <= high - 1; j++) {
        if(arr[j] <= pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Função recursiva Quick Sort
void quickSort(int arr[], int low, int high) {
    int pi;
    if(low < high) {
        pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int NC, N, i;
    scanf("%d", &NC);

    while(NC--) {
        scanf("%d", &N);
        int *alturas = (int*)malloc(N * sizeof(int));

        for(i = 0; i < N; i++) {
            scanf("%d", &alturas[i]);
        }

        quickSort(alturas, 0, N - 1);

        for(i = 0; i < N; i++) {
            if(i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");

        free(alturas);
    }

    return 0;
}
