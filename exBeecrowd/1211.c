#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compara(const void* a, const void* b){
    const char* str_a = *(const char**)a;
    const char* str_b = *(const char**)b;
    return strcmp(str_a, str_b);
}

int prefixo_comum(const char* s1, const char* s2){
    int count = 0;
    while(*s1 &&(*s1 == *s2)){
        count++;
        s1++;
        s2++;
    }
    return count;
}

int main(){
    int N;
    
    while(scanf("%d", &N) != EOF){
        char** lista_tel = (char**) malloc(N * sizeof(char*));
        if(lista_tel == NULL) return 1;

        int i;
        for(i = 0; i < N; i++){
            lista_tel[i] = (char*) malloc(201 * sizeof(char));
            if(lista_tel[i] == NULL) return 1;
            scanf("%s", lista_tel[i]);
        }

        qsort(lista_tel, N, sizeof(char*), compara);

        long long economia = 0;
        for(i = 0; i < N - 1; i++){
            economia += prefixo_comum(lista_tel[i], lista_tel[i + 1]);
        }
        printf("%lld\n", economia);
        for(i = 0; i < N; i++){
            free(lista_tel[i]);
        }
        free(lista_tel);
    }
    return 0;
}