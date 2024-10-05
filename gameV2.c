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
    char action;
} Nave;

typedef struct {
    int pos_x;
    int pos_y;
} Projetil_Nave;

typedef struct {
    int vida;
    int pos_x;
    int pos_y;
    int time_move;
    char sprite;
} Inimigo;


// Inicializando as variáveis de game, jogador e projetil
Game game;
Nave jogador;
Projetil_Nave projetil;
Inimigo inimigo_1;
Inimigo inimigo_2;
Inimigo inimigo_3;

// Criar funções necessárias
void carregar_config_game() {
    game.janela_x = TAMANHO_JANELA;
    game.janela_y = TAMANHO_JANELA;
    game.score = 0;
    game.hiScore = 0;
}

void carregar_config_jogador() {
    jogador.action = '0';
    jogador.disparo = 0;
    jogador.vidas = 3;
    jogador.pos_x = TAMANHO_JANELA / 2;
    jogador.pos_y = TAMANHO_JANELA - 2;

}

void carregar_config_inimigos() {
    char sprite = 'M';
    inimigo_1.pos_x = 2;
    inimigo_1.pos_y = 2;
    inimigo_1.sprite = sprite;
    inimigo_1.vida = 1;

    inimigo_2.pos_x = inimigo_1.pos_x + 2;
    inimigo_2.pos_y = inimigo_1.pos_y;
    inimigo_2.sprite = sprite;
    inimigo_2.vida = 1;

    inimigo_3.pos_x = inimigo_2.pos_x + 2;
    inimigo_3.pos_y = inimigo_1.pos_y;
    inimigo_3.sprite = sprite;
    inimigo_3.vida = 1;
}

void actions_jogador() {
    printf(">> ");
    scanf("%c", &jogador.action);

    // Faz o jogador ir para a esquerda
    if (jogador.action == 'a' || jogador.action == 'A') {
        jogador.pos_x--;
    }

    // Faz o jogador ir para a direita
    else if (jogador.action == 'd' || jogador.action == 'D') {
        jogador.pos_x++;
    }

    // Faz o jogador disparar um projétil
    else if (jogador.action == 'w' || jogador.action == 'W') {
        // verificando se o jogador não está com um projétil ativo
        // Essa condicional faz com que o jogador possa disparar
        // apenas quando não existir um projétil;
        if (jogador.disparo == 0){
            jogador.disparo = 1;
            projetil.pos_x = jogador.pos_x;
            projetil.pos_y = jogador.pos_y - 1;
        }

    }
    getchar();
}

void limpar_tela() {
    system("CLS");
}

void carregar_tela() {
    printf("SCORE   HI-SCORE   VIDAS\n");
    printf(" %d         %d         %d\n", game.score, game.hiScore, jogador.vidas);
    for (int i = 0; i < game.janela_x; i++) {
        for (int j = 0; j < game.janela_y; j++) {
            if (game.score > game.hiScore) {
                game.hiScore = game.score;
            }
            // Verificando se o projétil atingiu a borda ou algum inimigo
            if (jogador.disparo == 1) {
                if (projetil.pos_y <= 0) {
                    jogador.disparo = 0;
                }

                else if (projetil.pos_y == inimigo_1.pos_y && projetil.pos_x == inimigo_1.pos_x && inimigo_1.vida > 0) {
                    jogador.disparo = 0;
                    inimigo_1.vida--;
                    game.score += 5;
                }

                else if (projetil.pos_y == inimigo_2.pos_y && projetil.pos_x == inimigo_2.pos_x && inimigo_2.vida > 0) {
                    jogador.disparo = 0;
                    inimigo_2.vida--;
                    game.score += 5;
                }

                else if (projetil.pos_y == inimigo_3.pos_y && projetil.pos_x == inimigo_3.pos_x && inimigo_3.vida > 0) {
                    jogador.disparo = 0;
                    inimigo_3.vida--;
                    game.score += 5;
                }
            }

            // Não deixa o jogador passar da borda direita
            if (jogador.pos_x >= game.janela_x - 1) {
                jogador.pos_x = game.janela_x - 2;
            }
            
            // Não deixa o jogador passar da borda esquerda
            if (jogador.pos_x <= 0) {
                jogador.pos_x = 1;
            }

            // Adicionando os inimigos no jogo
            if (inimigo_1.pos_x == j && inimigo_1.pos_y == i && inimigo_1.vida > 0) {
                printf("%c ", inimigo_1.sprite);
            }

            else if (inimigo_2.pos_x == j && inimigo_2.pos_y == i && inimigo_2.vida > 0) {
                printf("%c ", inimigo_2.sprite);
            }

            else if (inimigo_3.pos_x == j && inimigo_3.pos_y == i && inimigo_3.vida > 0) {
                printf("%c ", inimigo_3.sprite);
            }

            // criando as bordas da matriz
            else if (i == 0 || j == 0 || i == game.janela_x - 1 || j == game.janela_y - 1 || jogador.pos_x == j && jogador.pos_y == i) {
                if (jogador.pos_x == j && jogador.pos_y == i) {
                    // adicionando o jogador na matriz
                    printf("^ ");
                }

                else {
                    printf("* ");
                }
            }

            else {
                // verificando se o jogador disparou
                if (jogador.disparo == 1 && projetil.pos_y == i && projetil.pos_x == j) {
                    printf(". ");
                    projetil.pos_y--;
    
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
    carregar_config_inimigos();

    while(1) {
        if (jogador.vidas > 0){
            limpar_tela();
            carregar_tela();
            actions_jogador();
        }

        else {
            break;
        }
    }

    return 0;
}
