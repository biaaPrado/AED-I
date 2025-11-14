#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V 50 
#define INF 1000000

int adj[MAX_V][MAX_V]; 
int dist[MAX_V][MAX_V];
int grau[MAX_V];
int visitado[MAX_V];

int odd_nodes[MAX_V];    
int dp[1 << 21]; 
int dist_odd[MAX_V][MAX_V]; 

int solve_mwm(int mask, int k) {
    if (dp[mask] != -1) {
        return dp[mask];
    }
    if (mask == 0) {
        return 0;
    }

    int res = INF;
    int i;
    for (i = 0; i < k; i++) {
        if (mask & (1 << i)) {
            break;
        }
    }

    for (int j = i + 1; j < k; j++) {
        if (mask & (1 << j)) {
            int nova_mask = mask ^ (1 << i) ^ (1 << j);
            int custo = dist_odd[i][j] + solve_mwm(nova_mask, k);
            if (custo < res) {
                res = custo;
            }
        }
    }
    
    dp[mask] = res;
    return res;
}


int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, V, A;
        scanf("%d", &N); // Nó inicial (irrelevante)
        scanf("%d %d", &V, &A); // Vértices e Arestas

        memset(grau, 0, sizeof(grau));
        memset(visitado, 0, sizeof(visitado));
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = (i == j) ? 0 : INF;
            }
        }

        int custo_total = A; 

        for (int i = 0; i < A; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u][v] = adj[v][u] = 1; 
            grau[u]++;
            grau[v]++;
        }

        for (int i = 0; i < V; i++) {
            if (grau[i] > 0 && !visitado[i]) {
                // --- 1. Encontra o Componente ---
                int comp_nodes[MAX_V];
                int comp_size = 0;
                
                int q[MAX_V]; 
                int q_frente = 0, q_tras = 0;
                
                q[q_tras++] = i;
                visitado[i] = 1;
                comp_nodes[comp_size++] = i;

                while (q_frente < q_tras) {
                    int u = q[q_frente++];
                    for (int v = 0; v < V; v++) {
                        if (adj[u][v] == 1 && !visitado[v]) {
                            visitado[v] = 1;
                            comp_nodes[comp_size++] = v;
                            q[q_tras++] = v;
                        }
                    }
                }

                // --- 2. Encontra nós ímpares e calcula caminhos (FW) ---
                int k_odd = 0; 
                
                int map_node[MAX_V];
                memset(map_node, -1, sizeof(map_node));
                for(int j=0; j < comp_size; j++) map_node[comp_nodes[j]] = j;

                for(int r=0; r < comp_size; r++) {
                    for(int c=0; c < comp_size; c++) {
                        if (r == c) dist[r][c] = 0;
                        else dist[r][c] = (adj[comp_nodes[r]][comp_nodes[c]] == 1) ? 1 : INF;
                    }
                }
                
                for (int k = 0; k < comp_size; k++) {
                    for (int r = 0; r < comp_size; r++) {
                        for (int c = 0; c < comp_size; c++) {
                            if (dist[r][k] + dist[k][c] < dist[r][c]) {
                                dist[r][c] = dist[r][k] + dist[k][c];
                            }
                        }
                    }
                }

                for (int j = 0; j < comp_size; j++) {
                    if (grau[comp_nodes[j]] % 2 != 0) {
                        odd_nodes[k_odd++] = comp_nodes[j];
                    }
                }
                
                if (k_odd > 0) {
                    // --- 3. Prepara a matriz de distância para o MWM ---
                    for(int r=0; r < k_odd; r++) {
                        for(int c=0; c < k_odd; c++) {
                            int no_r = map_node[odd_nodes[r]];
                            int no_c = map_node[odd_nodes[c]];
                            dist_odd[r][c] = dist[no_r][no_c];
                        }
                    }
                    
                    // --- 4. Resolve o MWM ---
                    int mascara_final = (1 << k_odd) - 1;
                    memset(dp, -1, sizeof(dp));
                    custo_total += solve_mwm(mascara_final, k_odd);
                }
            }
        }
        
        printf("%d\n", custo_total);
    }
    return 0;
}