#include <stdio.h>

#define TAMANHO 10
#define NAVIO 3
#define AGUA 0

int main() {
    // 1. Criar e inicializar o tabuleiro 10x10 com zeros (água)
    int tabuleiro[TAMANHO][TAMANHO];
    
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- POSICIONAMENTO DOS NAVIOS ---
    // Cada navio tem tamanho fixo 3, conforme as regras do nível intermediário.

    // Navio 1: Horizontal (Linha 2, Colunas 1, 2, 3)
    for (int j = 1; j <= 3; j++) {
        tabuleiro[2][j] = NAVIO;
    }

    // Navio 2: Vertical (Coluna 8, Linhas 4, 5, 6)
    for (int i = 4; i <= 6; i++) {
        tabuleiro[i][8] = NAVIO;
    }

    // Navio 3: Diagonal Principal (Descendente: linha e coluna aumentam)
    // Coordenadas: (1,1), (2,2), (3,3) -> Note que (2,2) é seguro pois o Navio 1 está na linha 2, colunas 1-3.
    // Vamos usar (5,1), (6,2), (7,3) para evitar qualquer risco de sobreposição.
    for (int k = 0; k < 3; k++) {
        tabuleiro[5 + k][1 + k] = NAVIO;
    }

    // Navio 4: Diagonal Secundária (Ascendente: linha aumenta, coluna diminui)
    // Coordenadas: (1,7), (2,6), (3,5)
    for (int k = 0; k < 3; k++) {
        tabuleiro[1 + k][7 - k] = NAVIO;
    }

    // --- EXIBIÇÃO DO TABULEIRO ---
    printf("--- Batalha Naval: Nivel Aventureiro ---\n\n");
    
    // Cabeçalho das colunas para facilitar a leitura
    printf("    ");
    for (int j = 0; j < TAMANHO; j++) printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%d | ", i); // Índice da linha
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}