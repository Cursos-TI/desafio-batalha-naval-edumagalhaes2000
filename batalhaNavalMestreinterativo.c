#include <stdio.h>
#include <stdbool.h>

#define TAMANHO 10
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define DESTRUIDO -1
#define ERROU_TIRO -2

// Função para exibir o mapa para o jogador
void exibirMapa(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\n   ");
    for (int j = 0; j < TAMANHO; j++) printf("%d ", j); // Cabeçalho colunas
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%d |", i); // Cabeçalho linhas
        for (int j = 0; j < TAMANHO; j++) {
            // Lógica de visualização (Oculta navios não atingidos)
            if (tabuleiro[i][j] == NAVIO) printf("~ "); // Água (escondendo navio)
            else if (tabuleiro[i][j] == DESTRUIDO) printf("X "); // Navio atingido
            else if (tabuleiro[i][j] == ERROU_TIRO) printf("O "); // Tiro na água
            else if (tabuleiro[i][j] == HABILIDADE) printf("? "); // Habilidade oculta
            else printf("~ "); // Água limpa
        }
        printf("\n");
    }
    printf("\n");
}

// Radar: Verifica as casas vizinhas (3x3)
void ativarRadar(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    printf("\n--- [RADAR ATIVADO em %d,%d] ---\n", linha, coluna);
    int naviosEncontrados = 0;

    for (int i = linha - 1; i <= linha + 1; i++) {
        for (int j = coluna - 1; j <= coluna + 1; j++) {
            if (i >= 0 && i < TAMANHO && j >= 0 && j < TAMANHO) {
                if (tabuleiro[i][j] == NAVIO) {
                    printf("(!) Navio detectado em: [%d, %d]\n", i, j);
                    naviosEncontrados++;
                }
            }
        }
    }
    if (naviosEncontrados == 0) printf("Nenhum navio detectado por perto.\n");
    printf("--------------------------------\n\n");
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0};
    int l, c;

    // --- SETUP FIXO DO CAMPO ---
    // Navio 1 (Diagonal)
    tabuleiro[0][0] = NAVIO; tabuleiro[1][1] = NAVIO; tabuleiro[2][2] = NAVIO;
    // Navio 2 (Horizontal)
    tabuleiro[5][7] = NAVIO; tabuleiro[5][8] = NAVIO; tabuleiro[5][9] = NAVIO;
    // Habilidade
    tabuleiro[1][2] = HABILIDADE;

    // Loop do Jogo
    while (1) {
        exibirMapa(tabuleiro); // 
        printf("Digite a coordenada de ataque (Linha Coluna): ");
        scanf("%d %d", &l, &c);

        if (l < 0 || l >= TAMANHO || c < 0 || c >= TAMANHO) {
            printf("Tiro invalido!\n");
            continue;
        }

        if (tabuleiro[l][c] == NAVIO) {
            printf("BUM! Navio atingido!\n");
            tabuleiro[l][c] = DESTRUIDO;
        } 
        else if (tabuleiro[l][c] == HABILIDADE) {
            printf("BOOM! Radar ativado!\n");
            ativarRadar(tabuleiro, l, c);
            tabuleiro[l][c] = ERROU_TIRO; // Habilidade usada vira tiro na água
        }
        else {
            printf("Agua...\n");
            if (tabuleiro[l][c] == AGUA) tabuleiro[l][c] = ERROU_TIRO;
        }
    }

    return 0;
}