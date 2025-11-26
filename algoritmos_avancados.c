#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definição da Struct Sala ---
// Representa cada cômodo da mansão como um nó na árvore binária.
typedef struct Sala {
    char nome[50];        // Nome da sala (ex: Cozinha, Biblioteca)
    struct Sala *esquerda; // Caminho para a sala à esquerda
    struct Sala *direita;  // Caminho para a sala à direita
} Sala;

// --- Função: criarSala ---
// Objetivo: Alocar dinamicamente uma nova sala na memória.
// Parâmetros: Nome da sala.
// Retorno: Ponteiro para a nova sala criada.
Sala* criarSala(char *nome) {
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// --- Função: explorarSalas ---
// Objetivo: Controlar a navegação do jogador pela árvore de salas.
// Parâmetros: Ponteiro para a sala atual (nó raiz inicial).
void explorarSalas(Sala *salaAtual) {
    char escolha;

    // Loop de navegação
    while (salaAtual != NULL) {
        printf("\n------------------------------------------------\n");
        printf("Voce esta em: [%s]\n", salaAtual->nome);

        // Verifica se é um nó folha (sem saídas)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\n[!] Este comodo nao tem saidas. Fim da linha!\n");
            printf("A investigacao neste caminho terminou.\n");
            break; // Encerra a exploração
        }

        printf("Para onde deseja ir?\n");
        
        // Mostra as opções disponíveis
        if (salaAtual->esquerda != NULL) 
            printf(" (e) Esquerda: %s\n", salaAtual->esquerda->nome);
        
        if (salaAtual->direita != NULL) 
            printf(" (d) Direita:  %s\n", salaAtual->direita->nome);

        printf(" (s) Sair da mansao\n");
        printf("Escolha: ");
        scanf(" %c", &escolha); // O espaço antes do %c limpa o buffer do teclado

        // Processa a decisão do jogador
        if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda;
            } else {
                printf("\n[X] Nao ha passagem para a esquerda!\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita;
            } else {
                printf("\n[X] Nao ha passagem para a direita!\n");
            }
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf("\nVoce decidiu sair da mansao. Ate a proxima!\n");
            break;
        } 
        else {
            printf("\n[!] Opcao invalida. Tente novamente.\n");
        }
    }
}

// --- Função Principal: main ---
// Objetivo: Montar a estrutura fixa do mapa (árvore) e iniciar o jogo.
int main() {
    // 1. Criação dos Cômodos (Nós)
    Sala *raiz = criarSala("Hall de Entrada");
    
    // Nível 1
    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Cozinha");
    
    // Nível 2 (Esquerda do Hall)
    raiz->esquerda->esquerda = criarSala("Biblioteca");
    raiz->esquerda->direita = criarSala("Jardim de Inverno");
    
    // Nível 2 (Direita do Hall)
    raiz->direita->esquerda = criarSala("Sala de Jantar");
    raiz->direita->direita = criarSala("Despensa");

    // Nível 3 (Algumas folhas finais)
    raiz->esquerda->esquerda->esquerda = criarSala("Passagem Secreta");
    
    // 2. Início do Jogo
    printf("=== DETECTIVE QUEST: MISTERY MANSION ===\n");
    printf("Objetivo: Explore os comodos para encontrar pistas.\n");
    
    explorarSalas(raiz);

    // Nota: Em um programa real complexo, seria ideal ter uma função para liberar
    // a memória (free) de todos os nós ao final, mas para este nível introdutório
    // o foco é na estrutura e navegação.
    
    return 0;
}