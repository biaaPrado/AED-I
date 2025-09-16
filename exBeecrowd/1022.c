#include <stdio.h>

// Função para calcular o MDC (Máximo Divisor Comum)
int mdc(int a, int b) {
    if (b == 0) return a;
    return mdc(b, a % b);
}

int main() {
    int N;
    scanf("%d", &N);

    while (N--) {
        int N1, D1, N2, D2;
        char op;

        scanf("%d / %d %c %d / %d", &N1, &D1, &op, &N2, &D2);

        int num, den; // resultado da operação

        if (op == '+') {
            num = N1 * D2 + N2 * D1;
            den = D1 * D2;
        } else if (op == '-') {
            num = N1 * D2 - N2 * D1;
            den = D1 * D2;
        } else if (op == '*') {
            num = N1 * N2;
            den = D1 * D2;
        } else if (op == '/') {
            num = N1 * D2;
            den = N2 * D1;
        }

        // Simplificação
        int divisor = mdc(num, den);
        int simp_num = num / divisor;
        int simp_den = den / divisor;

        // Força sinal no denominador (se negativo, passa para o numerador)
        if (simp_den < 0) {
            simp_den *= -1;
            simp_num *= -1;
        }

        printf("%d/%d = %d/%d\n", num, den, simp_num, simp_den);
    }

    return 0;
}
