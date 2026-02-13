#include <stdio.h>

#define TAMANHO 10
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5

// Função para exibir o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == NAVIO) printf("3 ");
            else if (tabuleiro[i][j] == HABILIDADE) printf("5 ");
            else printf("0 ");
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // 1. Posicionamento fixo de alguns navios (conforme níveis anteriores)
    for (int j = 1; j <= 3; j++) tabuleiro[2][j] = NAVIO; // Horizontal
    for (int i = 5; i <= 7; i++) tabuleiro[i][8] = NAVIO; // Vertical

    // 2. Definição das Matrizes de Habilidade (5x5)
    int cone[5][5] = {0}, cruz[5][5] = {0}, octaedro[5][5] = {0};

    // Construção dinâmica das formas usando condicionais
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // Lógica do CONE (Triângulo apontando para baixo)
            if (i == 0 && j == 2) cone[i][j] = 1;
            else if (i == 1 && j >= 1 && j <= 3) cone[i][j] = 1;
            else if (i == 2) cone[i][j] = 1;

            // Lógica da CRUZ
            if (i == 2 || j == 2) cruz[i][j] = 1;

            // Lógica do OCTAEDRO (Losango/Diamante)
            // Baseado na distância de Manhattan ao centro (2,2)
            int dist = (i > 2 ? i - 2 : 2 - i) + (j > 2 ? j - 2 : 2 - j);
            if (dist <= 2) octaedro[i][j] = 1;
        }
    }

    // 3. Integração ao Tabuleiro (Sobreposição)
    // Definimos pontos de origem (centro da matriz 5x5 no tabuleiro 10x10)
    int origens[3][2] = {{0, 4}, {4, 1}, {7, 4}}; // Cone, Cruz, Octaedro

    // Aplicando as habilidades
    for (int h = 0; h < 3; h++) {
        int oL = origens[h][0];
        int oC = origens[h][1];

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                // Cálculo da posição real no tabuleiro (centralizando a matriz 5x5)
                int realL = oL + i - 2;
                int realC = oC + j - 2;

                // Validação de limites (Check para não sair da matriz 10x10)
                if (realL >= 0 && realL < TAMANHO && realC >= 0 && realC < TAMANHO) {
                    // Seleciona qual matriz aplicar
                    int valorEfeito = 0;
                    if (h == 0) valorEfeito = cone[i][j];
                    else if (h == 1) valorEfeito = cruz[i][j];
                    else valorEfeito = octaedro[i][j];

                    // Sobrepõe apenas se for área de efeito (1) e não houver navio
                    if (valorEfeito == 1 && tabuleiro[realL][realC] != NAVIO) {
                        tabuleiro[realL][realC] = HABILIDADE;
                    }
                }
            }
        }
    }

    printf("--- BATALHA NAVAL: MESTRE ---\n");
    printf("Legenda: 0=Agua, 3=Navio, 5=Habilidade\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}