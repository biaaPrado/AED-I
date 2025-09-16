#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> // Adicionado para strchr

#define MAX 1001

typedef enum{
    NENHUM,
    OPERANDO,
    OPERADOR,
    ABRE_PARENTESES,
    FECHA_PARENTESES
}TipoToken;

// (Suas funções de Pilha e o enum TipoToken permanecem aqui, sem alterações)
typedef struct {
    char itens[MAX];
    int topo;
}Pilha;
void inicializa(Pilha *p) { p->topo = -1; }
int vazia(Pilha *p) { return p->topo == -1; }
void empilha(Pilha *p, char item) { p->itens[++p->topo] = item; }
char desempilha(Pilha *p){ return vazia(p) ? '\0' : p->itens[p->topo--]; }
char verTopo(Pilha *p){ return vazia(p) ? '\0' : p->itens[p->topo]; }


// --- FUNÇÕES CORRIGIDAS ---

int precedencia(char operador) {
    switch (operador) {
        case '^': return 6;
        case '*': case '/': return 5;
        case '+': case '-': return 4;
        case '>': case '<': case '=': case '#': return 3; // CORRIGIDO O TYPO
        case '.': return 2;
        case '|': return 1;
        default: return 0;
    }
}

int erroLexico(const char *expr){
    for(int i = 0; expr[i] != '\0'; i++){
        // strchr não é necessário aqui pois a main já remove os espaços
        if(!isalnum(expr[i]) && !strchr("+-*/^<>=#.|()", expr[i])){
            return 1;
        }
    }
    return 0;
}

void processaExpressao(const char *infixa){
    if(erroLexico(infixa)){
        printf("Lexical Error!\n");
        return;
    }

    Pilha pilha_op;
    inicializa(&pilha_op);

    char posfixa[MAX] = {0};
    int pos_idx = 0;

    TipoToken ultimo_token = NENHUM;
    int sintaxeErro = 0;

    for(int i = 0; infixa[i] != '\0' && !sintaxeErro; i++){
        char token = infixa[i];

        // CORREÇÃO 1: Tratar operandos primeiro
        if(isalnum(token)){
            if(ultimo_token == OPERANDO || ultimo_token == FECHA_PARENTESES){
                sintaxeErro = 1; // Ex: A B ou )A
            }
            posfixa[pos_idx++] = token;
            ultimo_token = OPERANDO;
        } else if(token == '('){
            if(ultimo_token == OPERANDO || ultimo_token == FECHA_PARENTESES){
                sintaxeErro = 1; // Ex: A( ou )(
            }
            empilha(&pilha_op, token);
            ultimo_token = ABRE_PARENTESES;
        } else if(token == ')'){
            if(ultimo_token == OPERADOR || ultimo_token == ABRE_PARENTESES){
                sintaxeErro = 1; // Ex: +) ou ()
            }
            while(!vazia(&pilha_op) && verTopo(&pilha_op) != '('){
                posfixa[pos_idx++] = desempilha(&pilha_op);
            }
            // CORREÇÃO 2: Verificar se o '(' existe antes de desempilhar
            if(vazia(&pilha_op)){
                sintaxeErro = 1; // ')' sem '(' correspondente
            } else {
                desempilha(&pilha_op); // Remove o '('
            }
            ultimo_token = FECHA_PARENTESES;
        } else { // Se for um operador
            // CORREÇÃO 3: Verificação de sintaxe mais completa
            if(ultimo_token != OPERANDO && ultimo_token != FECHA_PARENTESES){
                sintaxeErro = 1; // Ex: ++, *A, (+A
            }
            while(!vazia(&pilha_op) && verTopo(&pilha_op) != '(' && 
                  precedencia(verTopo(&pilha_op)) >= precedencia(token)){
                posfixa[pos_idx++] = desempilha(&pilha_op);
            }
            empilha(&pilha_op, token);
            ultimo_token = OPERADOR;
        }
    }

    // Verificações finais
    if(ultimo_token == OPERADOR || ultimo_token == ABRE_PARENTESES) sintaxeErro = 1;
    
    if(!sintaxeErro){
        while(!vazia(&pilha_op)){
            char topo = desempilha(&pilha_op);
            // CORREÇÃO 4: Verificar se sobrou algum '(' na pilha
            if(topo == '('){
                sintaxeErro = 1;
                break;
            }
            posfixa[pos_idx++] = topo;
        }
    }

    if(sintaxeErro){
        printf("Syntax Error!\n");
    } else {
        posfixa[pos_idx] = '\0';
        printf("%s\n", posfixa);
    }
}

int main(){
    char linha[MAX];
    // CORREÇÃO 5: Usando fgets para leitura segura de linhas
    while(fgets(linha, sizeof(linha), stdin) != NULL){
        // Remove o '\n' do final que o fgets captura
        linha[strcspn(linha, "\r\n")] = '\0';

        char expr[MAX];
        int j = 0;
        for(int i = 0; linha[i] != '\0'; i++){
            if(linha[i] != ' ' && linha[i] != '\t'){
                expr[j++] = linha[i];
            }
        }
        expr[j] = '\0';

        if(strlen(expr) > 0){
            processaExpressao(expr);
        }
    }
    return 0;
}