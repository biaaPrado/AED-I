#include <stdio.h>
#include <stdlib.h>

void heapify(int arr[], int n, int i) {
    int largest = i; // inicializa o maior como raiz
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    // comparar com o filho esquerdo
    if(left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // comparar com o filho direito
    if(right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // se a raiz não é o maior
    if(largest != i) {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest); // recursivamente
    }
}

void heapSort(int arr[], int n) {
    int i, temp;

    // Construir o heap
    for(i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extrair elementos do heap um por um
    for(i = n - 1; i >= 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
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

        heapSort(alturas, N);

        for(i = 0; i < N; i++) {
            if(i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");

        free(alturas);
    }

    return 0;
}
