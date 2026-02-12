#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Reutilizando nossa função de validação (crucial para o scanf)
int validarPosicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int col, int orientacao) {
    if (orientacao == 0) { // Horizontal
        if (col + TAM_NAVIO > TAM_TABULEIRO) return 0;
        for (int i = 0; i < TAM_NAVIO; i++) if (tabuleiro[linha][col + i] != 0) return 0;
    } else { // Vertical
        if (linha + TAM_NAVIO > TAM_TABULEIRO) return 0;
        for (int i = 0; i < TAM_NAVIO; i++) if (tabuleiro[linha + i][col] != 0) return 0;
    }
    return 1;
}

void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n    ");
    for (int j = 0; j < TAM_TABULEIRO; j++) printf("%d ", j);
    printf("\n   %s\n", "--------------------");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d | ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%c ", (tabuleiro[i][j] == 3 ? 'N' : '~'));
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};
    int linha, col, orientacao;

    printf("--- POSICIONAMENTO DE NAVIO ---\n");

    for (int n = 1; n <= 2; n++) { // Loop para posicionar 2 navios
        int sucesso = 0;
        while (!sucesso) {
            printf("\nNavio %d (Tamanho %d):\n", n, TAM_NAVIO);
            printf("Digite a linha (0-9): ");
            scanf("%d", &linha);
            printf("Digite a coluna (0-9): ");
            scanf("%d", &col);
            printf("Orientacao (0 para Horizontal, 1 para Vertical): ");
            scanf("%d", &orientacao);

            if (validarPosicao(tabuleiro, linha, col, orientacao)) {
                for (int i = 0; i < TAM_NAVIO; i++) {
                    if (orientacao == 0) tabuleiro[linha][col + i] = 3;
                    else tabuleiro[linha + i][col] = 3;
                }
                sucesso = 1;
                printf("Navio posicionado com sucesso!\n");
                exibirTabuleiro(tabuleiro);
            } else {
                printf("!!! Erro: Posicao invalida ou ocupada. Tente novamente. !!!\n");
            }
        }
    }

    printf("\nConfiguracao final concluida!\n");
    return 0;
}