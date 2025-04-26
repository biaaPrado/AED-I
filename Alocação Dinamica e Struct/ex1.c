#include<stdio.h>
#include<stdlib.h>

typedef struct{`
    float dinheiro;
    int qtde;
    float* precos;
}Cliente;

void lerDados(Cliente *clientes, int n){
    int i;
    for(i=0; i<n; i++){
        scanf("%f %d", &clientes[i].dinheiro, &clientes[i].qtde);


    }
}

int ordena(const void* p0, const void* p1){
    float fp0 = *(float*)p0;
    float fp1 = *(float*)p1;
    if (p0 < p1) 
        return -1;
    else if(p0 > p1)
        return 1;
    else
        return 0;
}

int main()