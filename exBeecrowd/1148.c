#include <stdio.h>
#include <string.h>

#define MAX_N 501
#define INF 0x3f3f3f3f

typedef struct {
    int N;
    int costs_input[MAX_N][MAX_N];
    int costs_fw[MAX_N][MAX_N];
} GraphData;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int N, E, K, O, D;

    while (scanf("%d %d", &N, &E) == 2 && (N != 0 || E != 0)) {
        
        GraphData g;
        g.N = N;

        memset(g.costs_input, 0x3f, sizeof(g.costs_input));
        
        for (int i = 0; i < E; i++) {
            int X, Y, H;
            scanf("%d %d %d", &X, &Y, &H);
            g.costs_input[X][Y] = H;
        }

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i == j) {
                    g.costs_fw[i][j] = 0;
                }
                else if (g.costs_input[i][j] < INF && g.costs_input[j][i] < INF) {
                    g.costs_fw[i][j] = 0;
                } else {
                    g.costs_fw[i][j] = g.costs_input[i][j];
                }
            }
        }

        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    g.costs_fw[i][j] = min(g.costs_fw[i][j], 
                                           g.costs_fw[i][k] + g.costs_fw[k][j]);
                }
            }
        }

        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            scanf("%d %d", &O, &D);
            int M = g.costs_fw[O][D];
            
            if (M == INF) {
                printf("Nao e possivel entregar a carta\n");
            } else {
                printf("%d\n", M);
            }
        }
        printf("\n");
    }

    return 0;
}