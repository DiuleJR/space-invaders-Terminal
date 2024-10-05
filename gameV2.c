#include <stdio.h>
#include <stdlib.h>

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

// Criar funções necessárias

// jogar tudo na função principal