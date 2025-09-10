#include <stdio.h>

#define N 9

// Função para verificar se uma linha é válida
int verificaLinha(int matriz[N][N], int linha) {
    int freq[10] = {0}, j; 
    for (j = 0; j < N; j++) {
        int num = matriz[linha][j];
        if (num < 1 || num > 9) return 0;
        if (freq[num]) return 0; // repetido
        freq[num] = 1;
    }
    return 1;
}

// Função para verificar se uma coluna é válida
int verificaColuna(int matriz[N][N], int coluna) {
    int freq[10] = {0}, i;
    for (i = 0; i < N; i++) {
        int num = matriz[i][coluna];
        if (num < 1 || num > 9) return 0;
        if (freq[num]) return 0;
        freq[num] = 1;
    }
    return 1;
}

// Função para verificar se um bloco 3x3 é válido
int verificaBloco(int matriz[N][N], int linha, int coluna) {
    int freq[10] = {0}, i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            int num = matriz[linha + i][coluna + j];
            if (num < 1 || num > 9) return 0;
            if (freq[num]) return 0;
            freq[num] = 1;
        }
    }
    return 1;
}

int verificaSudoku(int matriz[N][N]) {
    int i, j;
    for (i = 0; i < N; i++) {
        if (!verificaLinha(matriz, i)) return 0;
    }
    // verifica colunas
    for (j = 0; j < N; j++) {
        if (!verificaColuna(matriz, j)) return 0;
    }
    // verifica blocos 3x3
    for (i = 0; i < N; i += 3) {
        for (j = 0; j < N; j += 3) {
            if (!verificaBloco(matriz, i, j)) return 0;
        }
    }
    return 1;
}

int main() {
    int T, i, j, caso;
    scanf("%d", &T);

    for (caso = 1; caso <= T; caso++) {
        int matriz[N][N];
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                scanf("%d", &matriz[i][j]);
            }
        }

        printf("Instancia %d\n", caso);
        if (verificaSudoku(matriz)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        printf("\n"); // linha em branco entre instâncias
    }

    return 0;
}
