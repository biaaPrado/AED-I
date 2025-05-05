#include<stdio.h>
#include<stdlib.h>

typedef struct{
    float dinheiro; //saldo da pessoa
    int qtde; //qtde de livros desejada
    float* precos; //vetor dos preços dos livros desejados
}Cliente;

void lerDados(Cliente *clientes, int n){ //recebe a struct como paramêtro e a qntd de clientes
    int i, j;

    for(i=0; i<n; i++){
        float D;
        int Q;

        do{
            scanf("%f", &D); //lê qntd de livros
        }while(D < 0);

        do{
            scanf("%d", &Q); //lê o saldo
        }while(Q < 0 || Q > 100);

        clientes[i].dinheiro = D;
        clientes[i].qtde = Q;

        clientes[i].precos = (float*) malloc(Q * sizeof(float)); //aloca espaços para os preços
            
        for (j=0; j<Q; j++){ //recebe os precos dos livros escolhidos pelo cliente
            do{
                scanf("%f", &clientes[i].precos[j]);
            }while(clientes[i].precos[j]<0);
        }
    }
}


void calculaGasto(Cliente *clientes, int n){
    int i, j;
    for(i=0; i<n; i++){
        int livrosComprados = 0;
        int Q = clientes[i].qtde;
        float saldoCliente = clientes[i].dinheiro;

        for(j=0; j<Q; j++){
           if(saldoCliente >= clientes[i].precos[j]){
                saldoCliente -= clientes[i].precos[j];
                livrosComprados++;
           }
        }

        printf("%d %.2f\n", livrosComprados, saldoCliente);
    }
}

int main(){
    int n;
    
    do{
        scanf("%d", &n);
    }while(n<1 || n>100);

    Cliente *clientes = (Cliente*) malloc(n * sizeof(Cliente)); //aloca espaço para a struct clientes

    if(clientes == NULL){
        return 0;
    }

    lerDados(clientes, n);
    calculaGasto(clientes, n);
    int i;

    for(i=0; i<n; i++){
        free(clientes[i].precos);
    }
    free(clientes); //libera o espaço de memória alocado para os clientes

    return 0;
}