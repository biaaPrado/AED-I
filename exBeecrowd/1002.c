#include <stdio.h>

int main(){
    double raio, area, pi;
    pi = 3.14159;

    scanf("%lf", &raio);
    area = raio * raio * 3.14159;
    printf("A=%.4lf\n", area);
    return 0;
}