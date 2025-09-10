#include <stdio.h>
 
int main() {
    char nome[20];
    double salario, vendas, total_salario;
    scanf("%s %lf %lf", &nome, &salario, &vendas);
    
    total_salario = salario + (vendas * 0.15);

    printf("TOTAL = R$ %.2lf\n", total_salario);
       
    return 0;
}