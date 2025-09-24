#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar cada criança na lista
typedef struct Crianca {
    char nome[31];
    int valor;
    struct Crianca* proximo;
    struct Crianca* anterior;
} Crianca;

int main() {
    int N;

    while (scanf("%d", &N) == 1 && N != 0) {
        
        // --- 1. Construção da Lista ---
        Crianca* head = (Crianca*)malloc(sizeof(Crianca));
        scanf("%s %d", head->nome, &head->valor);
        head->proximo = head;
        head->anterior = head;
        
        Crianca* current = head;
        for (int i = 1; i < N; i++) {
            Crianca* nova_crianca = (Crianca*)malloc(sizeof(Crianca));
            scanf("%s %d", nova_crianca->nome, &nova_crianca->valor);
            
            nova_crianca->anterior = current;
            nova_crianca->proximo = head;
            current->proximo = nova_crianca;
            head->anterior = nova_crianca;
            current = nova_crianca;
        }

        int num_restantes = N;
        int valor_atual = head->valor; // Valor da ficha para a primeira rodada
        Crianca* ponteiro_atual = head; // Onde a contagem vai começar

        // --- 2. Primeira Eliminação (Regra Especial) ---
        // "iniciando na criança que está ao lado da primeira"
        if (valor_atual % 2 != 0) { // Ímpar -> Horário
            ponteiro_atual = ponteiro_atual->proximo;
        } else { // Par -> Anti-horário
            ponteiro_atual = ponteiro_atual->anterior;
        }

        // Damos valor-1 passos a partir do ponto de início
        if (valor_atual % 2 != 0) { // Ímpar -> Horário
            for (int i = 0; i < valor_atual - 1; i++) {
                ponteiro_atual = ponteiro_atual->proximo;
            }
        } else { // Par -> Anti-horário
            for (int i = 0; i < valor_atual - 1; i++) {
                ponteiro_atual = ponteiro_atual->anterior;
            }
        }

        // --- 3. Loop para as Eliminações Subsequentes ---
        while (num_restantes > 1) {
            // Guarda o valor para a próxima rodada
            valor_atual = ponteiro_atual->valor;
            
            Crianca* a_remover = ponteiro_atual;
            
            // Define o ponto de partida da PRÓXIMA rodada
            if (valor_atual % 2 != 0) { // Se o valor do REMOVIDO é ímpar
                ponteiro_atual = a_remover->proximo;
            } else { // Se o valor do REMOVIDO é par
                ponteiro_atual = a_remover->anterior;
            }

            // Remove o nó da lista
            a_remover->anterior->proximo = a_remover->proximo;
            a_remover->proximo->anterior = a_remover->anterior;
            free(a_remover);
            num_restantes--;

            if (num_restantes == 1) break;

            // Realiza a contagem para a próxima eliminação
            // (valor da ficha do que foi removido, a partir do novo ponteiro_atual)
            if (valor_atual % 2 != 0) { // Ímpar -> Horário
                for (int i = 0; i < valor_atual - 1; i++) {
                    ponteiro_atual = ponteiro_atual->proximo;
                }
            } else { // Par -> Anti-horário
                for (int i = 0; i < valor_atual - 1; i++) {
                    ponteiro_atual = ponteiro_atual->anterior;
                }
            }
        }
        
        // --- 4. Imprime o Vencedor ---
        printf("Vencedor(a): %s\n", ponteiro_atual->nome);
        free(ponteiro_atual);
    }

    return 0;
}