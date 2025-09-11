#include <stdio.h>

int main() {
    int n, h, min, seg;
    scanf("%d", &n);
    h = n / 3600;
    min = (n % 3600) / 60;
    seg = n % 60;
    printf("%d:%d:%d\n", h, min, seg);
    
    return 0;
}
