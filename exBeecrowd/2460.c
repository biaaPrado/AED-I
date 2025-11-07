#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Para usar o tipo 'bool' (true/false)

#define MAX_ID 100001 // O ID máximo é 100000, então o vetor precisa ir até o índice 100000.

int main() {
    int N; // Quantidade inicial de pessoas
    scanf("%d", &N);

    // 1. Aloca dinamicamente o vetor para a fila inicial
    int *fila_inicial = (int *) malloc(N * sizeof(int));
    if (fila_inicial == NULL) return 1; // Erro de alocação

    // Lê os IDs da fila inicial
    for (int i = 0; i < N; i++) {
        scanf("%d", &fila_inicial[i]);
    }

    int M; // Quantidade de pessoas que desistiram
    scanf("%d", &M);

    // 2. Cria a tabela de consulta para os desistentes
    // calloc aloca e inicializa a memória com 0 (que para bool é 'false')
    bool *desistiu = (bool *) calloc(MAX_ID, sizeof(bool));
    if (desistiu == NULL) {
        free(fila_inicial); // Libera a memória já alocada
        return 1;
    }

    // 3. Lê os IDs dos desistentes e marca na tabela
    for (int i = 0; i < M; i++) {
        int id_desistente;
        scanf("%d", &id_desistente);
        desistiu[id_desistente] = true; // Marca que esta pessoa desistiu
    }

    // 4. Percorre a fila inicial e imprime quem não desistiu
    bool primeiro_a_imprimir = true;
    for (int i = 0; i < N; i++) {
        int id_atual = fila_inicial[i];
        
        // A consulta é instantânea: O(1)
        if (!desistiu[id_atual]) {
            // Lógica para imprimir o espaço corretamente
            if (!primeiro_a_imprimir) {
                printf(" ");
            }
            printf("%d", id_atual);
            primeiro_a_imprimir = false;
        }
    }
    printf("\n");

    // 5. Libera toda a memória alocada dinamicamente
    free(fila_inicial);
    free(desistiu);

    return 0;
}