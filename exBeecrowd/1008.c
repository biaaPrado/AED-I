#include <stdio.h>
 
int main() {
    int num, horas;
    float valor_hora, salario;
    scanf("%d %d %f", &num, &horas, &valor_hora);
    salario = horas * valor_hora;
    printf("NUMBER = %d\n", num);
    printf("SALARY = U$ %.2f\n", salario);
   
    return 0;
}