#include <stdio.h>
 
int main() {
    int km;
    float litros, consumo;
    scanf("%d %f", &km, &litros);
    consumo = km / litros;
    printf("%.3f km/l\n", consumo);
    
    return 0;
}