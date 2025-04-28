#include<stdio.h>
#include<stdlib.h>

typedef struct{
    float dinheiro; //saldo da pessoa
    int qtde; //qtde de livros desejada
    float* precos; //vetor dos preços dos livros desejados
}Cliente;

int ordena(const void* p0, const void* p1){
    float fp0 = *(float*)p0;
    float fp1 = *(float*)p1;
    if (fp0 < fp1) 
        return -1;
    else if(fp0 > fp1)
        return 1;
    else
        return 0;
}


void lerDados(Cliente *clientes, int n){ //recebe a struct como paramêtro e a qntd de clientes
    int i, j;

    for(i=0; i<n; i++){
        float D;
        int Q;

        scanf("%f %d", &D, &Q); //lê o saldo e qntd de livros, fazendo as devidas verificações

        if(D < 0 || Q < 0 || Q > 100){
            exit(0);
        }

        clientes[i].dinheiro = D;
        clientes[i].qtde = Q;

        clientes[i].precos = (float*) malloc(Q * sizeof(float)); //aloca espaços para os preços
        if(clientes[i].precos == NULL){
            exit(0);
        }

        float* P = clientes[i].precos; 
    

        for (j=0; j<Q; j++){ //recebe os precos dos livros escolhidos pelo cliente
            scanf("%f", &P[j]); 
            if(P[j]<0){
                exit(0);
            }
        }

        qsort(P, Q, sizeof(float), ordena); //ordena os preços em ordem crescente
    }
}


void calculaGasto(Cliente *clientes, int n){
    int i, j;
    for(i=0; i<n; i++){
        int livrosComprados = 0;
        int Q = clientes[i].qtde;
        float saldoCliente = clientes[i].dinheiro;
        float* P = clientes[i].precos;

        for(j=0; j<Q; j++){
           if(saldoCliente >= P[j]){
                saldoCliente -= P[j];
                livrosComprados++;
           }else{
                break;
           }
        }

        printf("%d %.2f\n", livrosComprados, saldoCliente);

        free(P); //libera o espaço de memória alocado pelo vetor de preços
    }
}

int main(){
    int n;
    scanf("%d", &n);

    if(n<=0 || n>100){ //verifica se a quantidade de clientes é válida no intervalo
        return 0;
    }
    if(n == 0){
        return 0;
    }

    Cliente *clientes = (Cliente*) malloc(n * sizeof(Cliente)); //aloca espaço para a struct clientes

    if(clientes == NULL){
        return 0;
    }

    lerDados(clientes, n);
    calculaGasto(clientes, n);

    free(clientes); //libera o espaço de memória alocado para os clientes

    return 0;
}