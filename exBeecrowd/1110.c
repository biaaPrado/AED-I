#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó (elemento) da lista ligada/fila
typedef struct No {
    int data;
    struct No* prox;
} No;

// Estrutura para a Fila, que armazena ponteiros para o início e o fim
typedef struct {
    No* inicio; // Ponteiro para o primeiro nó (frente)
    No* fim;    // Ponteiro para o último nó (traseira)
    int tamanho;
} Queue;

// Função para criar e inicializar uma nova fila vazia
Queue* cria() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        exit(1); // Encerra se a alocação falhar
    }
    q->inicio = NULL;
    q->fim = NULL;
    q->tamanho = 0;
    return q;
}

// ---- FUNÇÃO CRÍTICA CORRIGIDA ----
// Função para adicionar um elemento ao final da fila (enqueue)
void enqueue(Queue* q, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        exit(1);
    }
    novo->data = valor;
    novo->prox = NULL;

    // LÓGICA CORRETA:
    // Caso 1: A fila está VAZIA.
    if (q->fim == NULL) {
        // O novo nó é tanto o início quanto o fim.
        q->inicio = novo;
        q->fim = novo;
    }
    // Caso 2: A fila NÃO está vazia.
    else {
        // O "próximo" do antigo fim aponta para o novo nó.
        q->fim->prox = novo;
        // O ponteiro de fim da fila é atualizado para o novo nó.
        q->fim = novo;
    }
    q->tamanho++;
}

// Função para remover um elemento do início da fila (dequeue)
int dequeue(Queue* q) {
    // Se a fila está vazia, não há nada a fazer.
    if (q->inicio == NULL) {
        return -1; // Retorna um valor de erro
    }

    // Guarda o nó a ser removido e o seu valor
    No* temp = q->inicio;
    int valor = temp->data;

    // Avança o ponteiro 'inicio' para o próximo elemento
    q->inicio = q->inicio->prox;

    // Se a fila ficou vazia após a remoção, o fim também deve ser NULL
    if (q->inicio == NULL) {
        q->fim = NULL;
    }

    free(temp); // Libera a memória do nó que foi removido
    q->tamanho--;
    return valor;
}

// Função para liberar toda a memória usada pela fila
void libera(Queue* q) {
    // Continua removendo nós até a fila estar vazia
    while (q->inicio != NULL) {
        dequeue(q);
    }
    // Libera a estrutura da própria fila
    free(q);
}

// Função que executa a simulação do jogo
void game(int n) {
    if (n <= 0) return;
    if (n == 1) { // Caso especial para n=1 para evitar malloc(0) e laços desnecessários
        printf("Discarded cards:\n");
        printf("Remaining card: 1\n");
        return;
    }

    Queue* cardDeck = cria();

    // Aloca memória para guardar as n-1 cartas descartadas
    int* discardedCards = (int*)malloc((n - 1) * sizeof(int));
    if (discardedCards == NULL) {
        libera(cardDeck);
        exit(1);
    }
    int discardedCount = 0;

    // Popula a fila com as cartas de 1 a n
    for (int i = 1; i <= n; i++) {
        enqueue(cardDeck, i);
    }

    // Processo principal do jogo
    while (cardDeck->tamanho > 1) {
        // 1. Descarta a carta do topo
        discardedCards[discardedCount++] = dequeue(cardDeck);

        // 2. Move a próxima carta para o fim (se ainda houver cartas)
        if (cardDeck->tamanho > 0) {
            int cardToMove = dequeue(cardDeck);
            enqueue(cardDeck, cardToMove);
        }
    }

    // A carta que sobrou
    int remainingCard = (cardDeck->inicio != NULL) ? cardDeck->inicio->data : 0;

    // Imprime o resultado
    printf("Discarded cards: %d", discardedCards[0]);
    for (int i = 1; i < discardedCount; i++) {
        printf(", %d", discardedCards[i]);
    }
    printf("\n");
    printf("Remaining card: %d\n", remainingCard);

    // Libera toda a memória alocada
    free(discardedCards);
    libera(cardDeck);
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        game(n);
    }
    return 0;
}