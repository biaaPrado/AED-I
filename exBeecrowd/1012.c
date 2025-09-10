#include <stdio.h>
 
int main() {
    double a, b, c;
    double pi = 3.14159;
    double area_triangulo, area_circulo, area_trapezio, area_quadrado, area_retangulo;
    
    scanf("%lf %lf %lf", &a, &b, &c);
    area_triangulo = (a*c)/2;
    area_circulo = pi*c*c;
    area_trapezio = ((a+b)*c)/2;
    area_quadrado = b*b;
    area_retangulo = a*b;

    printf("TRIANGULO: %.3f\n", area_triangulo);
    printf("CIRCULO: %.3f\n", area_circulo);
    printf("TRAPEZIO: %.3f\n", area_trapezio);
    printf("QUADRADO: %.3f\n", area_quadrado);
    printf("RETANGULO: %.3f\n", area_retangulo);

    return 0;
}