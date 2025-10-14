#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    while (scanf("%d", &n) != EOF) {
        
        int stack[1001], queue[1001], pq[1001];
        int stack_top = -1, queue_front = 0, queue_rear = 0, pq_size = 0;

        int is_stack = 1, is_queue = 1, is_pq = 1;

        for (int i = 0; i < n; i++) {
            int command, value;
            scanf("%d %d", &command, &value);

            if (command == 1) { // Operação de Inserção
                if (is_stack) stack[++stack_top] = value;
                if (is_queue) queue[queue_rear++] = value;
                if (is_pq) pq[pq_size++] = value;

            } else { // Operação de Remoção (o valor esperado é 'value')
                if (is_stack) {
                    if (stack_top < 0 || stack[stack_top--] != value) {
                        is_stack = 0; // Se a remoção falhar, não pode ser uma pilha.
                    }
                }
                
                // Verifica a Fila (FIFO)
                if (is_queue) {
                    if (queue_front >= queue_rear || queue[queue_front++] != value) {
                        is_queue = 0; // Se a remoção falhar, não pode ser uma fila.
                    }
                }

                // Verifica a Fila de Prioridade (maior elemento)
                if (is_pq) {
                    if (pq_size <= 0) {
                        is_pq = 0; 
                    } else {
                        // Encontra e "remove" o maior elemento
                        int max_val = -1, max_idx = -1;
                        for (int j = 0; j < pq_size; j++) {
                            if (pq[j] > max_val) {
                                max_val = pq[j];
                                max_idx = j;
                            }
                        }
                        
                        if (max_idx == -1 || max_val != value) {
                            is_pq = 0; // Se a remoção falhar, não pode ser uma FP.
                        } else {
                            pq[max_idx] = pq[pq_size - 1];
                            pq_size--;
                        }
                    }
                }
            }
        }

        int sum = is_stack + is_queue + is_pq;
        if (sum == 0) {
            printf("impossible\n");
        } else if (sum > 1) {
            printf("not sure\n");
        } else {
            if (is_stack) printf("stack\n");
            else if (is_queue) printf("queue\n");
            else printf("priority queue\n");
        }
    }
    return 0;
}