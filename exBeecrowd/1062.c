#include <stdio.h>

int main() {
    int N;

    while (scanf("%d", &N), N) {
        while (1) {
            int desired[1000];
            scanf("%d", &desired[0]);

            if (desired[0] == 0) {
                printf("\n");
                break;
            }

            for (int i = 1; i < N; i++) scanf("%d", &desired[i]);

            int stack[1000], top = -1;
            int next = 1;  // próximo vagão que chega
            int possible = 1;

            for (int i = 0; i < N; i++) {
                int target = desired[i];

                // empurrar vagões até alcançar o desejado
                while (next <= N && (top == -1 || stack[top] != target)) {
                    stack[++top] = next++;
                }

                if (stack[top] == target) {
                    top--; // tira da pilha
                } else {
                    possible = 0;
                    break;
                }
            }

            if (possible) printf("Yes\n");
            else printf("No\n");
        }
    }

    return 0;
}
