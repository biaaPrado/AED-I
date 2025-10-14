#include <stdio.h>
#include <stdlib.h>

// A estrutura do Nó está perfeita.
typedef struct No {
    int chave;
    struct No* proximo;
} No;

// A função para liberar a memória está perfeita.
void liberar_lista(No* inicio) {
    No* atual = inicio;
    No* temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

int main() {
    int N, M, C;
    scanf("%d", &N); // Lê o número de casos de teste

    for (int i = 0; i < N; i++) {
        // Adiciona a linha em branco entre os casos de teste (exceto antes do primeiro)
        if (i > 0) {
            printf("\n");
        }

        scanf("%d %d", &M, &C); // Lê o tamanho da tabela e o número de chaves

        // Alocação e inicialização estão corretas.
        No** tabela_hash = (No**) malloc(M * sizeof(No*));
        for (int j = 0; j < M; j++) {
            tabela_hash[j] = NULL;
        }

        // Leitura das chaves e inserção na tabela
        for (int j = 0; j < C; j++) {
            int chave;
            scanf("%d", &chave);

            int indice = chave % M;

            // Aloca o novo nó
            No* novoNo = (No*) malloc(sizeof(No));
            novoNo->chave = chave;
            novoNo->proximo = NULL; // O novo nó será sempre o último

            // --- INÍCIO DA CORREÇÃO ---
            // Se a lista naquele índice está vazia, o novo nó é o primeiro.
            if (tabela_hash[indice] == NULL) {
                tabela_hash[indice] = novoNo;
            } else {
                // Se a lista não está vazia, percorre até o último nó.
                No* atual = tabela_hash[indice];
                while (atual->proximo != NULL) {
                    atual = atual->proximo;
                }
                // Adiciona o novo nó no final.
                atual->proximo = novoNo;
            }
            // --- FIM DA CORREÇÃO ---
        }

        // A lógica de impressão está correta.
        for (int j = 0; j < M; j++) {
            printf("%d -> ", j);
            No* atual = tabela_hash[j];
            while (atual != NULL) {
                printf("%d -> ", atual->chave);
                atual = atual->proximo;
            }
            printf("\\\n");
        }
        
        // A lógica de liberação de memória está correta.
        for (int j = 0; j < M; j++) {
            liberar_lista(tabela_hash[j]);
        }
        free(tabela_hash);
    }

    return 0;
}