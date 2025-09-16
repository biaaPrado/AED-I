#include <stdio.h>
#include <math.h>

int main() {
    int N, cidade = 1;
    while (scanf("%d", &N) && N != 0) {
        int i, moradores, consumo;
        int totalMoradores = 0, totalConsumo = 0;

        // Vetor para acumular moradores por consumo arredondado
        int freq[201] = {0}; // consumo máximo por pessoa será <= 200

        for (i = 0; i < N; i++) {
            scanf("%d %d", &moradores, &consumo);
            int consumoPessoa = consumo / moradores; // arredondar para baixo
            freq[consumoPessoa] += moradores;
            totalMoradores += moradores;
            totalConsumo += consumo;
        }

        // Imprime cabeçalho da cidade
        printf("Cidade# %d:\n", cidade++);

        // Lista em ordem crescente de consumo
        int first = 1;
        for (i = 0; i <= 200; i++) {
            if (freq[i] > 0) {
                if (!first) printf(" ");
                printf("%d-%d", freq[i], i);
                first = 0;
            }
        }
        printf("\n");

        // Consumo médio truncado com duas casas
        double media = (double) totalConsumo / totalMoradores;
        printf("Consumo medio: %.2lf m3.\n", floor(media * 100) / 100);

        // Linha em branco entre cidades
        if (scanf("%d", &N) && N != 0) {
            printf("\n");
            ungetc('\n', stdin); // devolve o número lido para o próximo loop
        } else {
            break;
        }
    }
    return 0;
}
