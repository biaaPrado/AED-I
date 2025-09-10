#include <stdio.h>
 
int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int diferenca = (a * b - c * d);
    printf("DIFERENCA = %d\n", diferenca);
   
    return 0;
}