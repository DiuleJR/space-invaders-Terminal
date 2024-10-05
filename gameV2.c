#include <stdio.h>
#include <stdlib.h>
#define TAMANHO_JANELA 9

// O TAMANHO_JANELA precisa ser um número ÍMPAR
// para a nave ficar centralizada na matriz.

// Criar as estruturas necessárias
// -- Game, Nave, Inimigos e Projéteis
typedef struct {
    int janela_x;
    int janela_y;
    int score;
    int hiScore;
} Game;

typedef struct {
    int vidas;
    int pos_x;
    int pos_y;
    int disparo;
} Nave;

typedef struct {
    int pos_x;
    int pos_y;
} Projetil_Nave;

typedef struct {
    int vida;
    int pos_x;
    int pos_y;
} Inimigo;


// Inicializando as variáveis de game e jogador
Game game;
Nave jogador;

// Criar funções necessárias
void carregar_config_game() {
    game.janela_x = TAMANHO_JANELA;
    game.janela_y = TAMANHO_JANELA;
    game.score = 0;
    game.hiScore = 0;
}

void carregar_config_jogador() {
    jogador.vidas = 3;
    jogador.pos_x = TAMANHO_JANELA - 2;
    jogador.pos_y = TAMANHO_JANELA / 2;
}

void carregar_tela() {
    for (int i = 0; i < game.janela_x; i++) {
        for (int j = 0; j < game.janela_y; j++) {
            // criando as bordas da matriz
            if (i == 0 || j == 0 || i == game.janela_x - 1 || j == game.janela_y - 1) {
                printf("* ");
            }

            else {
                // adicionando o jogador na matriz
                if (jogador.pos_x == i && jogador.pos_y == j) {
                    printf("^ ");
                }
                else {
                    printf("  ");
                }
            }
        }
        printf("\n");
    }
}

// jogar tudo na função principal
int main () {

    carregar_config_game();
    carregar_config_jogador();
    carregar_tela();

    return 0;
}
