#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int coluna;
    int valor;
    struct No* prox;
}No;

typedef struct{
    No** linhas;
    int tam;
}MEsparsa;

MEsparsa* criaMatriz(int tam){
    MEsparsa* matriz = malloc(sizeof(MEsparsa));
    matriz->tam = tam;
    matriz->linhas = malloc(tam * sizeof(No*));

    int i;
    for(i=0; i<tam; i++){
        matriz->linhas[i] = NULL;
    }
    return matriz;
}

void insereElemento(MEsparsa* matriz, int linha, int coluna, int valor){
    if(valor == 0) return;
    No* novo = malloc(sizeof(No));
    novo->coluna = coluna;
    novo->valor = valor;
    novo->prox = matriz->linhas[linha];
    matriz->linhas[linha] = novo;
}

void liberaMatriz(MEsparsa* matriz){
    int i;
    for(i=0; i<matriz->tam; i++){
        No* atual = matriz->linhas[i];
        while(atual){
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(matriz->linhas);
    free(matriz);
}

MEsparsa* lerMatriz(int tam){
    MEsparsa* matriz = criaMatriz(tam);
    int i, j;
    for(i=0; i<tam; i++){
        for(j=0; j<tam; j++){
            int valor;
            if(scanf("%d", &valor) != 1){
                printf("Erro na leitura dos valores da matriz.\n");
                liberaMatriz(matriz);
                return NULL;
            }
            insereElemento(matriz, i, j, valor);
        }
    }
    return matriz;
}

MEsparsa* somaMatriz(MEsparsa* A, MEsparsa* B){
    MEsparsa* C = criaMatriz(A->tam);

    int i;
    for(i=0; i<A->tam; i++){
        
        No *pA;
        for(pA = A->linhas[i]; pA; pA = pA->prox)
            insereElemento(C, i, pA->coluna, pA->valor);

        No *pB;    
        for(pB= B->linhas[i]; pB; pB = pB->prox){
            No *pC = C->linhas[i];
            int find = 0;

            while(pC && !find){
                if(pC->coluna == pB->coluna){
                    pC->valor += pB->valor;
                    find = 1;
                }
                pC = pC->prox;
            }
            if(!find) insereElemento(C, i, pB->coluna, pB->valor);
        }
    }
    return C;
}

MEsparsa* subtraiMatriz(MEsparsa* A, MEsparsa* B){
    MEsparsa* C = criaMatriz(A->tam);

    int i;
    for(i=0; i<A->tam; i++){
        
        No *pA;
        for(pA = A->linhas[i]; pA; pA = pA->prox)
            insereElemento(C, i, pA->coluna, pA->valor);
        
        No *pB;
        for(pB = B->linhas[i]; pB; pB = pB->prox){
            No *pC = C->linhas[i];
            int find = 0;

            while(pC && !find){
                if(pC->coluna == pB->coluna){
                    pC->valor -= pB->valor;
                    find = 1;
                }
                pC = pC->prox;
            }
            if(!find) insereElemento(C, i, pB->coluna, -pB->valor);
        }
    }
    return C;
}

MEsparsa* multMatriz(MEsparsa* A, MEsparsa* B){
    MEsparsa* C = criaMatriz(A->tam);

    int i, j, soma;
    for(i=0; i<A->tam; i++){
        for(j=0; j<B->tam; j++){
            soma = 0;
            
            No *pA;
            for(pA = A->linhas[i]; pA; pA=pA->prox){
                No *pB = B->linhas[pA->coluna];
                int find = 0;

                while(pB && !find){
                    if(pB->coluna == j){
                        soma += pA->valor * pB->valor;
                        find = 1;
                    }
                    pB = pB->prox;
                }
            }
            if(soma != 0) insereElemento(C, i, j, soma);
        }
    }
    return C;
}

void imprimeMatriz(MEsparsa* matriz){
    int i, j;
    for(i=0; i<matriz->tam; i++){
        No* atual = matriz->linhas[i];
        for(j=0; j<matriz->tam; j++){
            No* temp = atual;
            int impresso = 0;
            while(temp && !impresso){
                if(temp->coluna == j){
                    printf("%d ", temp->valor);
                    impresso = 1;
                }
                temp = temp->prox; 
            }
            if(!impresso) printf("0 ");
        }
        printf("\n");
    }
}

int main(){
    int op, tam;

    if(scanf("%d", &op) != 1 || op < 1 || op > 3){
        return 0;
    }

    if(scanf("%d", &tam) != 1 || tam < 1){
        return 0;
    }

    MEsparsa *A = lerMatriz(tam);
    MEsparsa *B = lerMatriz(tam);
    MEsparsa *resultado = NULL;

    if(op == 1) resultado = somaMatriz(A, B);
    if(op == 2) resultado = subtraiMatriz(A, B);
    if(op == 3) resultado = multMatriz(A, B);

    imprimeMatriz(resultado);

    liberaMatriz(A);
    liberaMatriz(B);
    liberaMatriz(resultado);

    return 0;
}