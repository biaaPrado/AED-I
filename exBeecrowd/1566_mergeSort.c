#include <stdio.h>
#include <stdlib.h>

// Função para mesclar duas metades do vetor
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int i, j, k;

    // Criando vetores temporários
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for(i = 0; i < n1; i++) L[i] = arr[left + i];
    for(j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Função recursiva de Merge Sort
void mergeSort(int arr[], int left, int right) {
    int mid;
    if(left < right) {
        mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int NC;  // número de cidades
    int i, N;
    scanf("%d", &NC);

    while(NC--) {
        scanf("%d", &N);
        int *alturas = (int*)malloc(N * sizeof(int));

        for(i = 0; i < N; i++) {
            scanf("%d", &alturas[i]);
        }

        mergeSort(alturas, 0, N - 1);

        for(i = 0; i < N; i++) {
            if(i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");

        free(alturas);
    }

    return 0;
}
