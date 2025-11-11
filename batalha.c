#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int i, j;

    // Inicializa o tabuleiro com água (0)
    for (i = 0; i < TAM_TABULEIRO; i++) {
        for (j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Adiciona um navio exemplo (3)
    tabuleiro[2][3] = 3;
    tabuleiro[2][4] = 3;
    tabuleiro[2][5] = 3;

    // MATRIZES DAS HABILIDADES
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    int meio = TAM_HABILIDADE / 2; // centro

    // --- CONE ---
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= meio - i && j <= meio + i && i <= meio)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // --- CRUZ ---
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (i == meio || j == meio)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    // --- OCTAEDRO (sem usar abs) ---
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            int diffI = (i - meio < 0) ? -(i - meio) : (i - meio);
            int diffJ = (j - meio < 0) ? -(j - meio) : (j - meio);

            if (diffI + diffJ <= meio)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }

    // --- POSIÇÕES DE ORIGEM ---
    int origemConeLinha = 1, origemConeColuna = 1;
    int origemCruzLinha = 5, origemCruzColuna = 5;
    int origemOctaedroLinha = 7, origemOctaedroColuna = 2;

    int linhaTab, colunaTab;

    // --- SOBREPOSIÇÃO CONE ---
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (cone[i][j] == 1) {
                linhaTab = origemConeLinha + i;
                colunaTab = origemConeColuna + j;
                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO && colunaTab >= 0 && colunaTab < TAM_TABULEIRO) {
                    if (tabuleiro[linhaTab][colunaTab] == 0)
                        tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }

    // --- SOBREPOSIÇÃO CRUZ ---
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (cruz[i][j] == 1) {
                linhaTab = origemCruzLinha + i - meio;
                colunaTab = origemCruzColuna + j - meio;
                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO && colunaTab >= 0 && colunaTab < TAM_TABULEIRO) {
                    if (tabuleiro[linhaTab][colunaTab] == 0)
                        tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }

    // --- SOBREPOSIÇÃO OCTAEDRO ---
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (octaedro[i][j] == 1) {
                linhaTab = origemOctaedroLinha + i - meio;
                colunaTab = origemOctaedroColuna + j - meio;
                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO && colunaTab >= 0 && colunaTab < TAM_TABULEIRO) {
                    if (tabuleiro[linhaTab][colunaTab] == 0)
                        tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }

    // --- EXIBE TABULEIRO ---
    printf("   ");
    for (j = 0; j < TAM_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (i = 0; i < TAM_TABULEIRO; i++) {
        printf("%c  ", 'A' + i);
        for (j = 0; j < TAM_TABULEIRO; j++) {
            int valor = tabuleiro[i][j];
            if (valor == 0)
                printf("~ "); // água
            else if (valor == 3)
                printf("# "); // navio
            else if (valor == 5)
                printf("* "); // área da habilidade
        }
        printf("\n");
    }

    return 0;
}