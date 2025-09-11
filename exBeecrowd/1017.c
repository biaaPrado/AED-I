#include <stdio.h>

int main(){
    int tempo, vMedia, distancia;
    float litros;

    scanf("%d", &tempo);
    scanf("%d", &vMedia);
    distancia = tempo * vMedia;
    litros = distancia / 12.0;
    printf("%.3f\n", litros);
    
    return 0;
}