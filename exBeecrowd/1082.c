#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int grafo[26][26];
int visitado[26];
char componente[27];
int tam_componente;

int comparar_char(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

void dfs(int u, int V) {
    visitado[u] = 1;
    componente[tam_componente] = u + 'a';
    tam_componente++;

    for (int v = 0; v < V; v++) {
        if (grafo[u][v] == 1 && visitado[v] == 0) {
            dfs(v, V);
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for (int caso = 1; caso <= N; caso++) {
        int V, E;
        scanf("%d %d", &V, &E);

        memset(grafo, 0, sizeof(grafo));
        memset(visitado, 0, sizeof(visitado));

        for (int i = 0; i < E; i++) {
            char c1, c2;
            scanf(" %c %c", &c1, &c2);

            int u = c1 - 'a';
            int v = c2 - 'a';

            grafo[u][v] = 1;
            grafo[v][u] = 1;
        }

        printf("Case #%d:\n", caso);
        int num_componentes = 0;

        for (int i = 0; i < V; i++) {
            if (visitado[i] == 0) {
                tam_componente = 0;
                dfs(i, V);
                num_componentes++;

                qsort(componente, tam_componente, sizeof(char), comparar_char);

                for (int j = 0; j < tam_componente; j++) {
                    printf("%c,", componente[j]);
                }
                printf("\n");
            }
        }

        printf("%d connected components\n", num_componentes);
        
        printf("\n");
    }

    return 0;
}