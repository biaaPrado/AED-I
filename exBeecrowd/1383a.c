#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int tabuleiro[9][9];
}Sudoku;

int validaLinha(Sudoku *s){
    int i, j;
    for(i = 0; i < 9; i++){
        int check[10] = {0};
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
    int i, j;
    for(j = 0; j < 9; j++){
        int check[10] = {0};
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
    int blocoLinha, blocoColuna, i, j;
    for(blocoLinha = 0; blocoLinha < 9; blocoLinha += 3){
        for(blocoColuna = 0; blocoColuna < 9; blocoColuna += 3){
            int check[10] = {0};
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
        Sudoku s;
        
        int i, j;
        for(i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                scanf("%d", &s.tabuleiro[i][j]);
            }
        }

        int linhasValidas = validaLinha(&s);
        int colunasValidas = validaColuna(&s);
        int regioesValidas = validaRegioes(&s);

        printf("Instancia %d\n", instancia++);
        
        if(linhasValidas && colunasValidas && regioesValidas){
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        printf("\n");
    }
}