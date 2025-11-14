#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXM 30001

int head[MAXN], to[MAXM], nextE[MAXM];
int cor[MAXN];
int N, M, T;
int edgeCount;

int ciclo;

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextE[edgeCount] = head[u];
    head[u] = edgeCount;
    edgeCount++;
}

int dfs(int u) {
    cor[u] = 1;       // visitando

    for (int e = head[u]; e != -1; e = nextE[e]) {
        int v = to[e];

        if (cor[v] == 1) {
            return 1; // ciclo encontrado
        }
        else if (cor[v] == 0) {
            if (dfs(v)) return 1;
        }
    }

    cor[u] = 2;       // finalizado
    return 0;
}

int main() {
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d", &N, &M);

        // iniciar estruturas
        for (int i = 1; i <= N; i++) {
            head[i] = -1;
            cor[i] = 0;
        }

        edgeCount = 0;
        ciclo = 0;

        // ler arestas
        for (int i = 0; i < M; i++) {
            int A, B;
            scanf("%d %d", &A, &B);
            addEdge(A, B);
        }

        // DFS para achar ciclos
        for (int i = 1; i <= N && !ciclo; i++) {
            if (cor[i] == 0)
                if (dfs(i))
                    ciclo = 1;
        }

        printf(ciclo ? "SIM\n" : "NAO\n");
    }

    return 0;
}
