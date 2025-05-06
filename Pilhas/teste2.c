#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da pilha
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Definição de um ponteiro para o nó da pilha
typedef Node* PilhaPtr;

// Liberar a memória alocada para a pilha
void libera(PilhaPtr p) {
    if (p == NULL) return;
    libera(p->next);
    free(p);
}

// Verificar se a pilha está vazia
int isEmpty(PilhaPtr p) {
    return p == NULL;
}

// Obter o tamanho da pilha
int getSize(PilhaPtr p) {
    int count = 0;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

// Inserir elemento na pilha (PUSH)
void push(PilhaPtr* p, int value) {
    PilhaPtr newNode = (PilhaPtr)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        exit(1);
    }
    
    newNode->data = value;
    newNode->next = *p;
    *p = newNode;
}

// Remover elemento da pilha (POP)
void pop(PilhaPtr* p, int* value) {
    if (isEmpty(*p)) {
        printf("Erro: Pilha vazia!\n");
        exit(0);
    }
    
    PilhaPtr temp = *p;
    *value = temp->data;
    *p = temp->next;
    free(temp);
}

// Imprimir a pilha de forma recursiva
void imprime(PilhaPtr p) {
    if (p == NULL) return;
    printf("%d ", p->data);
    imprime(p->next);
}

// Imprimir a pilha completa com quebra de linha
void printStack(PilhaPtr p) {
    imprime(p);
    printf("\n");
}

// Duplicar o elemento do topo (DUP)
void dup(PilhaPtr* p) {
    if (isEmpty(*p)) {
        printf("Erro: Pilha vazia para DUP!\n");
        exit(0);
    }
    
    push(p, (*p)->data);
}

// Trocar os dois elementos do topo (SWAP)
void swap(PilhaPtr* p) {
    if (getSize(*p) < 2) {
        printf("Erro: Pilha insuficiente para SWAP!\n");
        exit(0);
    }
    
    int val1, val2;
    pop(p, &val1);
    pop(p, &val2);
    
    push(p, val1);
    push(p, val2);
}

// Mover o n-ésimo elemento para o topo (ROLL)
void roll(PilhaPtr* p, int n) {
    if (n <= 0 || getSize(*p) < n) {
        printf("Erro: Posicao invalida!\n");
        exit(0);
    }
    
    // Alocar memória para armazenar os elementos
    int* values = (int*)malloc(n * sizeof(int));
    if (values == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        exit(1);
    }
    
    // Retirar n elementos da pilha
    for (int i = 0; i < n; i++) {
        pop(p, &values[i]);
    }
    
    // Colocar n-1 elementos de volta na ordem inversa (exceto o n-ésimo)
    for (int i = n-2; i >= 0; i--) {
        push(p, values[i]);
    }
    
    // Colocar o n-ésimo elemento no topo
    push(p, values[n-1]);
    
    // Liberar memória
    free(values);
}

// Realizar operação de adição (ADD)
void add(PilhaPtr* p) {
    if (getSize(*p) < 2) {
        printf("Erro: Elementos insuficiente para operacao!\n");
        exit(0);
    }
    
    int val1, val2, resultado;
    pop(p, &val1);
    pop(p, &val2);
    
    resultado = val2 + val1;
    push(p, resultado);
}

// Realizar operação de subtração (SUB)
void sub(PilhaPtr* p) {
    if (getSize(*p) < 2) {
        printf("Erro: Elementos insuficiente para operacao!\n");
        exit(0);
    }
    
    int val1, val2, resultado;
    pop(p, &val1);
    pop(p, &val2);
    
    resultado = val2 - val1;
    push(p, resultado);
}

// Realizar operação de multiplicação (MUL)
void mul(PilhaPtr* p) {
    if (getSize(*p) < 2) {
        printf("Erro: Elementos insuficiente para operacao!\n");
        exit(0);
    }
    
    int val1, val2, resultado;
    pop(p, &val1);
    pop(p, &val2);
    
    resultado = val2 * val1;
    push(p, resultado);
}

// Realizar operação de divisão (DIV)
void div_op(PilhaPtr* p) {
    if (getSize(*p) < 2) {
        printf("Erro: Elementos insuficiente para operacao!\n");
        exit(0);
    }
    
    int val1, val2, resultado;
    pop(p, &val1);
    pop(p, &val2);
    
    if (val1 == 0) {
        printf("Erro: Divisao por zero!\n");
        exit(0);
    }
    
    resultado = val2 / val1;
    push(p, resultado);
}

// Limpar a pilha (CLEAR)
void clear(PilhaPtr* p) {
    libera(*p);
    *p = NULL;
}

int main() {
    PilhaPtr pilha = NULL;
    int lixo, n, valor;
    
    // Ler o número de comandos e validar
    do {
        scanf("%d", &n);
    } while (n < 1 || n > 100);
    
    getchar(); // Consumir o \n após o número
    
    // Processar cada comando
    for (int i = 0; i < n; i++) {
        char str[50], comando[10];
        
        // Ler a linha completa
        fgets(str, sizeof(str), stdin);
        
        // Separar o comando e o valor (se houver)
        sscanf(str, "%s %d", comando, &valor);
        
        // Executar o comando correspondente
        if (strcmp(comando, "PUSH") == 0) {
            push(&pilha, valor);
        } else if (strcmp(comando, "POP") == 0) {
            pop(&pilha, &lixo);
        } else if (strcmp(comando, "ADD") == 0) {
            add(&pilha);
        } else if (strcmp(comando, "SUB") == 0) {
            sub(&pilha);
        } else if (strcmp(comando, "MUL") == 0) {
            mul(&pilha);
        } else if (strcmp(comando, "DIV") == 0) {
            div_op(&pilha);
        } else if (strcmp(comando, "DUP") == 0) {
            dup(&pilha);
        } else if (strcmp(comando, "SWAP") == 0) {
            swap(&pilha);
        } else if (strcmp(comando, "ROLL") == 0) {
            roll(&pilha, valor);
        } else if (strcmp(comando, "CLEAR") == 0) {
            clear(&pilha);
        } else if (strcmp(comando, "PRINT") == 0) {
            printStack(pilha);
        }
        
        // Imprimir a pilha final se for o último comando e não for PRINT
        if (i == n-1 && strcmp(comando, "PRINT") != 0) {
            printStack(pilha);
        }
    }
    
    // Liberar a memória alocada
    libera(pilha);
    
    return 0;
}