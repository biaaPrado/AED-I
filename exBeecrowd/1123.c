#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 250
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef struct {
    long long adj[N_MAX][N_MAX];
    int N, M, C, K;
    int rota[N_MAX];
    int esta_na_rota[N_MAX];
} ProblemaGrafo;

long long dijkstra_modificado(ProblemaGrafo *p, int cidade_alvo_rota) {
    long long dist[N_MAX];
    int visitado[N_MAX];

    memset(dist, 0x3f, sizeof(dist));
    memset(visitado, 0, sizeof(visitado));

    dist[p->K] = 0;

    for (int i = 0; i < p->N; i++) {
        int u = -1;
        long long min_dist = INF;
        for (int j = 0; j < p->N; j++) {
            if (!visitado[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        
        visitado[u] = 1;

        if (u == cidade_alvo_rota) break;

        for (int v = 0; v < p->N; v++) {
            if (p->esta_na_rota[v] && v != cidade_alvo_rota) {
                continue;
            }

            if (dist[u] + p->adj[u][v] < dist[v]) {
                dist[v] = dist[u] + p->adj[u][v];
            }
        }
    }
    
    return dist[cidade_alvo_rota];
}

int main() {
    ProblemaGrafo p; 

    while (scanf("%d %d %d %d", &p.N, &p.M, &p.C, &p.K) == 4 && (p.N || p.M || p.C || p.K)) {
        
        for (int i = 0; i < p.N; i++) {
            for (int j = 0; j < p.N; j++) {
                p.adj[i][j] = (i == j) ? 0 : INF;
            }
        }

        for (int i = 0; i < p.M; i++) {
            int u, v;
            long long custo;
            scanf("%d %d %lld", &u, &v, &custo);
            if (custo < p.adj[u][v]) {
                p.adj[u][v] = p.adj[v][u] = custo;
            }
        }

        memset(p.esta_na_rota, 0, sizeof(p.esta_na_rota));
        for (int i = 0; i < p.C; i++) {
            p.rota[i] = i;
            p.esta_na_rota[i] = 1;
        }

        long long custo_ate_fim[N_MAX] = {0};
        
        for (int i = p.C - 2; i >= 0; i--) {
            int cidade_atual = p.rota[i];
            int proxima_cidade = p.rota[i + 1];
            
            custo_ate_fim[i] = p.adj[cidade_atual][proxima_cidade] + custo_ate_fim[i + 1];
        }
        
        if (p.esta_na_rota[p.K]) {
            printf("%lld\n", custo_ate_fim[p.K]);
        
        } else {
            long long custo_total_minimo = INF;

            for (int i = 0; i < p.C; i++) {
                int cidade_alvo = p.rota[i];
                
                long long custo_p1 = dijkstra_modificado(&p, cidade_alvo);
                long long custo_p2 = custo_ate_fim[i];

                if (custo_p1 < INF) { 
                    if (custo_p1 + custo_p2 < custo_total_minimo) {
                        custo_total_minimo = custo_p1 + custo_p2;
                    }
                }
            }
            printf("%lld\n", custo_total_minimo);
        }
    }

    return 0;
}