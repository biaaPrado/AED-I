#include <stdio.h>
#include <string.h>

int mat[1001][1001]; 
int cor[1001]; 
int N, M;
int ciclo;

void dfs(int u) {
    cor[u] = 1; // visitando

    for (int v = 1; v <= N; v++) {
        if (mat[u][v]) {
            if (cor[v] == 1) {
                ciclo = 1;
                return;
            }
            else if (cor[v] == 0) {
                dfs(v);
                if (ciclo) return;
            }
        }
    }

    cor[u] = 2; // finalizado
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d", &N, &M);

        memset(mat, 0, sizeof(mat));
        memset(cor, 0, sizeof(cor));
        ciclo = 0;

        for (int i = 0; i < M; i++) {
            int A, B;
            scanf("%d %d", &A, &B);
            mat[A][B] = 1;
        }

        for (int i = 1; i <= N && !ciclo; i++) {
            if (cor[i] == 0)
                dfs(i);
        }

        if (ciclo) printf("SIM\n");
        else printf("NAO\n");
    }

    return 0;
}
