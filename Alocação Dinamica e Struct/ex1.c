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

        do{
            scanf("%f %d", &D, &Q); //lê o saldo e qntd de livros, fazendo as devidas verificações
        }while(D < 0 || Q < 0 || Q > 100);

        clientes[i].dinheiro = D;
        clientes[i].qtde = Q;

        clientes[i].precos = (float*) malloc(Q * sizeof(float)); //aloca espaços para os preços
        float* P = clientes[i].precos; 
    

        for (j=0; j<Q; j++){ //recebe os precos dos livros escolhidos pelo cliente
            scanf("%f", &P[j]); 
            while(P[j] < 0){ //verifica se o  preço dos livros é maior que 0
                scanf("%f", &P[j]);
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

        float total = 0.0;
        for(j=0; j<Q; j++){
            total += P[j];
        }

        if(saldoCliente + 0.0001 >= total){
            livrosComprados = Q;
            saldoCliente -= total; 
        }else{
            livrosComprados = 0;
        }

        printf("%d %.2f\n", livrosComprados, saldoCliente);

        free(P); //libera o espaço de memória alocado pelo vetor de preços
    }
}

int main(){
    int n;
    scanf("%d", &n);

    while(n<0 || n>100){ //verifica se a quantidade de clientes é válida no intervalo
        scanf("%d", &n);
    }

    Cliente *clientes = (Cliente*) malloc(n * sizeof(Cliente)); //aloca espaço para a struct clientes

    lerDados(clientes, n);
    calculaGasto(clientes, n);

    free(clientes); //libera o espaço de memória alocado para os clientes

    return 0;
}