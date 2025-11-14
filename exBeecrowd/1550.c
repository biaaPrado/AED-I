#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MAX_NODES 10000

typedef struct {
    int items[MAX_NODES];
    int inicio;
    int fim;
} Fila;

void inicializar_fila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

void enfileirar(Fila *f, int n) {
    f->items[f->fim++] = n;
}

int desenfileirar(Fila *f) {
    return f->items[f->inicio++];
}

int fila_vazia(Fila *f) {
    return f->inicio == f->fim;
}

int inverter(int n) {
    int reverso = 0;
    while (n > 0) {
        reverso = reverso * 10 + (n % 10);
        n /= 10;
    }
    return reverso;
}

int bfs(int a, int b) {
    static int dist[MAX_NODES];
    
    memset(dist, -1, sizeof(dist));

    Fila f;
    inicializar_fila(&f);

    dist[a] = 0;       
    enfileirar(&f, a); 

    while (!fila_vazia(&f)) {
        int atual = desenfileirar(&f);

        if (atual == b) {
            return dist[b];
        }

        int vizinho1 = atual + 1;
        
        if (vizinho1 < MAX_NODES && dist[vizinho1] == -1) {
            dist[vizinho1] = dist[atual] + 1; // Custo é 1 a mais
            enfileirar(&f, vizinho1);
        }

        int vizinho2 = inverter(atual);
        
        if (vizinho2 < MAX_NODES && dist[vizinho2] == -1) {
            dist[vizinho2] = dist[atual] + 1;
            enfileirar(&f, vizinho2);
        }
    }
    
    return -1; 
}

int main() {
    int T; 
    scanf("%d", &T);

    while (T--) {
        int A, B; 
        scanf("%d %d", &A, &B);
        printf("%d\n", bfs(A, B));
    }

    return 0;
}