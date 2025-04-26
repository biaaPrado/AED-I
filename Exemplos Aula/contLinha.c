#include <stdio.h>
#define tam 3200

int main(){
    FILE * parq;
    int cont = 0;
    char linhas[tam];
    parq = fopen("teste.txt", "r");
    if (parq == NULL){
        printf("Erro na abertura do arquivo!\n");
        return 1;
    }
    while (fgets(linhas, tam, parq)!= NULL){
        cont++;
    }
    printf("O arquivo possui %d linhas\n", cont);
    fclose(parq);
    return 0;
}