#include <stdio.h>
#include <stdlib.h> // Biblioteca para malloc, free e qsort

// Função de comparação para o qsort.
// Para ordenar em ordem DECRESCENTE, a lógica é (b - a).
int comparar_decrescente(const void *a, const void *b) {
    // Converte os ponteiros genéricos (void*) para ponteiros de inteiros
    // e depois obtém os valores para a comparação.
    int valor_a = *(const int *)a;
    int valor_b = *(const int *)b;

    // Se b > a, o resultado é positivo, e qsort colocará 'b' antes de 'a'.
    return valor_b - valor_a;
}

int main() {
    int N; // Número de casos de teste
    scanf("%d", &N);

    // Loop para cada caso de teste
    while (N--) {
        int M; // Número de alunos no caso de teste atual
        scanf("%d", &M);

        // 1. Alocação dinâmica dos vetores
        int *vetor_chegada = (int *) malloc(M * sizeof(int));
        int *vetor_ordenado = (int *) malloc(M * sizeof(int));

        // É uma boa prática verificar se a alocação foi bem-sucedida
        if (vetor_chegada == NULL || vetor_ordenado == NULL) {
            fprintf(stderr, "Falha na alocacao de memoria.\n");
            return 1; // Encerra o programa indicando um erro
        }

        // 2. Leitura dos dados, preenchendo ambos os vetores
        for (int i = 0; i < M; i++) {
            scanf("%d", &vetor_chegada[i]);
            vetor_ordenado[i] = vetor_chegada[i]; // Cria a cópia
        }

        // 3. Ordena o vetor de cópia em ordem decrescente
        qsort(vetor_ordenado, M, sizeof(int), comparar_decrescente);

        // 4. Compara os vetores e conta as posições inalteradas
        int contador_inalterados = 0;
        for (int i = 0; i < M; i++) {
            if (vetor_chegada[i] == vetor_ordenado[i]) {
                contador_inalterados++;
            }
        }

        // 5. Imprime o resultado
        printf("%d\n", contador_inalterados);

        // 6. Libera a memória alocada para este caso de teste
        free(vetor_chegada);
        free(vetor_ordenado);
    }

    return 0;
}