#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SCREEN_X 9
#define SCREEN_Y 9

int screen[SCREEN_X][SCREEN_Y];

typedef struct {
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

} Projetil;

Nave jogador;
Projetil bala;
Game game;

void carregar_vidas() {
    printf("     Vidas: %d ", jogador.vidas);
    for (int i = 0; i < jogador.vidas; i++) {
        printf("U ");
    }
}


void carregar_tela() {
    system("CLS");
    printf("SCORE    HI-SCORE     VIDAS\n");
    printf("  %d         %d         %d\n", game.score, game.hiScore, jogador.vidas);

    for (int i = 0; i < SCREEN_X; i++) {
        for (int j = 0; j < SCREEN_Y; j++) {
            
            if (bala.pos_x <= 0) {
                jogador.disparo = 0;
                // jogador.vidas--;
                game.score += 5;
                bala.pos_x = 999;
                bala.pos_y = 999;

                if (game.score > game.hiScore) {
                    game.hiScore = game.score;
                }
            }

            if (jogador.pos_y >= SCREEN_Y - 1) {
                jogador.pos_y = SCREEN_Y - 2;
            }

            if (jogador.pos_y <= 0) {
                jogador.pos_y = 1;
            }


            if (jogador.disparo == 1 && bala.pos_x == i && bala.pos_y == j) {
                    printf(". ");

            }

            if (i == 0 || j == 0 || i == SCREEN_X - 1 || j == SCREEN_Y - 1 || jogador.pos_x == i && jogador.pos_y == j) {
                
                if (jogador.pos_x == i && jogador.pos_y == j) { 
                    printf("^ ");
                }

                else {
                    printf("* ");
                }

                ///if (i == 0 && j == SCREEN_Y - 1) {
                ///    carregar_vidas();
                ///};
                
            }


            else {
                if (jogador.disparo == 1 && bala.pos_x == i && bala.pos_y == j) {
                    printf("");
                }

                else {
                    printf("  ");
                }
    
            }
        }
        printf("\n");
    }

    if (jogador.disparo == 1) {
        bala.pos_x--;
    }

    //printf("\nVidas ");
    //for (int i = 0; i < jogador.vidas; i++) {
    //    printf("O ");
    //}

}


int main () {

    game.hiScore = 0;

    do {
        jogador.vidas = 3;
        jogador.pos_x = SCREEN_X - 3;
        jogador.pos_y = SCREEN_Y / 2;
        jogador.disparo = 0;

        bala.pos_x = 999;
        bala.pos_y = 999;

        game.score = 0;

        int continuee = 0;

        char entrada = 'a';

        do {
            carregar_tela();

            if (jogador.vidas == 0) {
                break;
            }
            
            printf(">> ");
            scanf("%c", &entrada);

            if (entrada == 'a' || entrada == 'A') {
                jogador.pos_y--;
            }

            else if (entrada == 'd' || entrada == 'D') {
                jogador.pos_y++;
            }

            else if (entrada == 'w' || entrada == 'W') {
                if (jogador.disparo == 0) {
                    jogador.disparo = 1;
                    bala.pos_x = jogador.pos_x - 1;
                    bala.pos_y = jogador.pos_y;
                }
            }

            else if (entrada == 'x' || entrada == 'X') {
                jogador.vidas--;
            }

            // sleep(1)

            //system("CLS");
            getchar();
            

        } while (jogador.vidas > 0);

        system("CLS");

        printf("\t GAME OVER!!!!\n\n\n");

        printf("\t[1] Tentar novamente\n\t[2] Sair\n\t>> ");
        scanf("%d", &continuee);

        if (continuee == 2) {
            break;

        }

        getchar();
        system("CLS");

    }while(1);

    return 0;
}