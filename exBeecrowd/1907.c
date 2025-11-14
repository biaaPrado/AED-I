#include <stdio.h>
#include <string.h> 

#define MAX_R 1024
#define MAX_C 1024

char grid[MAX_R][MAX_C];
int visited[MAX_R][MAX_C]; 
int R, C; 


/**
 * @brief Struct para armazenar uma coordenada (r, c)
 */
typedef struct {
    int r, c;
} Ponto;

/**
 * @brief Struct para a Fila (Queue)
 * Vamos usar uma fila bem grande (baseada no número max de células)
 * para garantir que ela não estoure.
 */
#define MAX_FILA (MAX_R * MAX_C)
Ponto fila[MAX_FILA];
int fila_inicio;
int fila_fim;

void inicializar_fila() {
    fila_inicio = 0;
    fila_fim = 0;
}

void enfileirar(int r, int c) {
    fila[fila_fim].r = r;
    fila[fila_fim].c = c;
    fila_fim++;
}

Ponto desenfileirar() {
    return fila[fila_inicio++];
}

int fila_vazia() {
    return fila_inicio == fila_fim;
}

/**
 * @brief Realiza uma Busca em Largura (Flood Fill) iterativa
 * para marcar todos os '.' conectados em um componente.
 * @param r_inicio Linha inicial
 * @param c_inicio Coluna inicial
 */
void bfs(int r_inicio, int c_inicio) {
    inicializar_fila();

    enfileirar(r_inicio, c_inicio);
    visited[r_inicio][c_inicio] = 1;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!fila_vazia()) {
        Ponto atual = desenfileirar();

        for (int i = 0; i < 4; i++) {
            int nr = atual.r + dr[i]; 
            int nc = atual.c + dc[i]; 
            
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) {
                continue; 
            }
            if (grid[nr][nc] == 'o') {
                continue;
            }

            if (visited[nr][nc]) {
                continue;
            }

            visited[nr][nc] = 1;
            enfileirar(nr, nc);
        }
    }
}


int main() {
    scanf("%d %d", &R, &C);

    for (int i = 0; i < R; i++) {
        scanf("%s", grid[i]);
    }

    memset(visited, 0, sizeof(visited));

    int component_count = 0;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            // Se a célula é um '.' E ainda não foi visitada
            if (grid[i][j] == '.' && !visited[i][j]) {
                // Encontramos uma nova área!
                component_count++;
                
                bfs(i, j);
            }
        }
    }

    printf("%d\n", component_count);

    return 0;
}