#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TrieNode {
    int isEndOfWord; 
    struct TrieNode *children[2];
} TrieNode;

TrieNode* criar_no() {
    TrieNode *novo_no = (TrieNode *)malloc(sizeof(TrieNode));
    novo_no->isEndOfWord = 0;
    novo_no->children[0] = NULL;
    novo_no->children[1] = NULL;
    return novo_no;
}

void liberar_trie(TrieNode *no) {
    if (no == NULL) {
        return;
    }
    liberar_trie(no->children[0]);
    liberar_trie(no->children[1]);
    free(no);
}

int main() {
    TrieNode *raiz = criar_no();
    TrieNode *atual = raiz;
    
    int joias_unicas_count = 0;
    int c; 

    while ((c = getchar()) != EOF) {
        
        if (c == '(') {
            if (atual->children[0] == NULL) {
                atual->children[0] = criar_no();
            }
            atual = atual->children[0];
        } 
        else if (c == ')') {
            if (atual->children[1] == NULL) {
                atual->children[1] = criar_no();
            }
            atual = atual->children[1];
        } 
        else if (c == '\n') {
            
            if (atual != raiz && atual->isEndOfWord == 0) {
                atual->isEndOfWord = 1;
                joias_unicas_count++;
            }
            atual = raiz; 
        }
    }
    
    if (atual != raiz && atual->isEndOfWord == 0) {
        atual->isEndOfWord = 1;
        joias_unicas_count++;
    }

    printf("%d\n", joias_unicas_count);

    liberar_trie(raiz);

    return 0;
}