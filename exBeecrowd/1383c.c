#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **tabuleiro;
}Sudoku;

Sudoku* criarSudoku(){
    Sudoku *s = (Sudoku*) malloc(sizeof(Sudoku));
    if(s == NULL){ return NULL;  }

    s->tabuleiro = (int**) malloc(9 * sizeof(int*));
    if(s->tabuleiro == NULL){ 
        free(s); 
        return NULL;  
    }

    int i;
    for(i = 0; i < 9; i++){
        s->tabuleiro[i] = (int*) malloc(9 * sizeof(int));
        if(s->tabuleiro[i] == NULL){
            for(int j = 0; j < i; j++){
                free(s->tabuleiro[j]);
            }
            free(s->tabuleiro);
            free(s);
            return NULL;
        }
    }
    return s;
}

void liberarSudoku(Sudoku *s){
    if(s != NULL){
        for(int i = 0; i < 9; i++){
            free(s->tabuleiro[i]);
        }
        free(s->tabuleiro);
        free(s);
    }
}

int validaLinha(Sudoku *s){
    int i, j, k;
    for(i = 0; i < 9; i++){
        int check[10];
        for(k = 0; k < 9; k++){
            check[k] = 0;
        }

        for(j = 0; j < 9; j++){
            int num = s->tabuleiro[i][j];
            if(check[num] == 1){
                return 0;
            }
            check[num] = 1;
        }
    }
    return 1;
}

int validaColuna(Sudoku *s){
    int i, j, k;
    for(j = 0; j < 9; j++){
        int check[10];
        for(k = 0; k < 9; k++){
            check[k] = 0;
        }

        for(i = 0; i < 9; i++){
            int num = s->tabuleiro[i][j];
            if(check[num] == 1){
                return 0;
            }
            check[num] = 1;
        }
    }
    return 1;
}

int validaRegioes(Sudoku *s){
    int blocoLinha, blocoColuna, i, k, j;

    for(blocoLinha = 0; blocoLinha < 9; blocoLinha += 3){
        for(blocoColuna = 0; blocoColuna < 9; blocoColuna += 3){
            int check[10];
            for(k = 0; k < 9; k++){
                check[k] = 0;
            }

            for(i = blocoLinha; i < blocoLinha + 3; i++){
                for(j = blocoColuna; j < blocoColuna + 3; j++){
                    int num = s->tabuleiro[i][j];
                    if(check[num] == 1){
                        return 0;
                    }
                    check[num] = 1;
                }
            }
        }
    }
    return 1;
}

int main(){
    int n, instancia = 1;
    scanf("%d", &n);

    while(n--){
        Sudoku *s = criarSudoku();

        int i, j;
        for(i = 0; i < 9; i++){
            for(j = 0; j < 9; j++){
                scanf("%d", &s->tabuleiro[i][j]);
            }
        }

        printf("Instancia %d\n", instancia++);

        int linhasValidas = validaLinha(s);
        int colunasValidas = validaColuna(s);
        int regioesValidas = validaRegioes(s);
        
        if(linhasValidas && colunasValidas && regioesValidas){
            printf("SIM\n\n");
        } else {
            printf("NAO\n\n");
        }

        liberarSudoku(s);
    }
}
