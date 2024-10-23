#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define ALTURA 10
#define LARGURA 39
#define TOTAL_INIMIGOS_POR_FILA 15
#define TOTAL_INIMIGOS 45
#define ESPACO_VAZIO ' '
#define ATRASO_TIQUE 50

// --------- Criar as estrutras -------- //
typedef struct
{
    int game_over;
    int score;
    int hi_score;
} Jogo;

typedef struct
{
    int vidas;
    int pos_x;
    int pos_y;
    int disparo;
    char sprite;
} Jogador;

typedef struct
{
    int pos_x;
    int pos_y;
    char sprite;
} Projetil;

typedef struct
{
    int vida;
    int pos_x;
    int pos_y;
    int disparo;
    char sprite;
} Inimigo;

// --------- Definir Variáveis Necessárias -------- //
Jogo jogo;
Jogador jogador;
Projetil projetil;
Inimigo inimigos[TOTAL_INIMIGOS];
// ------------------- PARTE DO PROFESSOR K
HANDLE console;
CHAR_INFO bufferConsole[LARGURA * ALTURA];
COORD tamanhoBuffer = {LARGURA, ALTURA};
COORD posicaoCaractere = {0, 0};
SMALL_RECT areaEscritaConsole = {0, 0, LARGURA - 1, ALTURA - 1};

// --------- Criar Funções -------- //
void carregar_config_jogo()
{
    jogo.game_over = 0;
    jogo.hi_score = 0;
    jogo.score = 0;
}

void carregar_config_projetil()
{
    projetil.pos_x = 999;
    projetil.pos_y = 999;
    projetil.sprite = '^';
}

void carregar_config_jogador()
{
    jogador.vidas = 3;
    jogador.disparo = 0;
    jogador.pos_x = LARGURA / 2;
    jogador.pos_y = ALTURA - 3;
    jogador.sprite = 'A';
}

void carregar_menu_jogo()
{
    char escolha = ' ';

    char menu[11][43] = {
        "               SPACE_INVADERS              ",
        "+ - - - - - - - - - - - - - - - - - - - - +",
        "|                                         |",
        "|            >> NEW GAME            +     |",
        "|  *                                      |",
        "|               RANKING      *            |",
        "|                                         |",
        "|               COMO JOGAR                |",
        "|       *                                 |",
        "|               QUIT                      |",
        "+ - - - - - - - - - - - - - - - - - - - - +"};

    while (1)
    {
        system("CLS");
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 43; j++)
            {
                printf("%c", menu[i][j]);
            }
            printf("\n");
        }

        escolha = getch();

        if (escolha == 'w' || escolha == 'W')
        {
            if (menu[3][13] == '>')
            {
                menu[3][13] = ' ';
                menu[3][14] = ' ';

                menu[9][13] = '>';
                menu[9][14] = '>';
            }

            else if (menu[9][13] == '>')
            {
                menu[9][13] = ' ';
                menu[9][14] = ' ';

                menu[7][13] = '>';
                menu[7][14] = '>';
            }

            else if (menu[7][13] == '>')
            {
                menu[7][13] = ' ';
                menu[7][14] = ' ';

                menu[5][13] = '>';
                menu[5][14] = '>';
            }

            else if (menu[5][13] == '>')
            {
                menu[5][13] = ' ';
                menu[5][14] = ' ';

                menu[3][13] = '>';
                menu[3][14] = '>';
            }
        }

        else if (escolha == 's' || escolha == 'S')
        {
            if (menu[3][13] == '>')
            {
                menu[3][13] = ' ';
                menu[3][14] = ' ';

                menu[5][13] = '>';
                menu[5][14] = '>';
            }

            else if (menu[5][13] == '>')
            {
                menu[5][13] = ' ';
                menu[5][14] = ' ';

                menu[7][13] = '>';
                menu[7][14] = '>';
            }

            else if (menu[7][13] == '>')
            {
                menu[7][13] = ' ';
                menu[7][14] = ' ';

                menu[9][13] = '>';
                menu[9][14] = '>';
            }

            else if (menu[9][13] == '>')
            {
                menu[9][13] = ' ';
                menu[9][14] = ' ';

                menu[3][13] = '>';
                menu[3][14] = '>';
            }
        }

        else if (escolha == 'e' || escolha == 'E')
        {
            if (menu[3][13] == '>')
            {
                system("CLS");
                break;
            }

            //
        }

        escolha = ' ';
    }
}

void carregar_config_inimigo()
{

    int filas_inimigos = 3;

    int intervalo_inimigos = 2;

    // Centraliza os inimigos
    int inimigo_x_inicial = (LARGURA - (TOTAL_INIMIGOS_POR_FILA - 1) * intervalo_inimigos) / 2;
    int inimigo_y_inicial = 1;

    int inimigo_contador = 0;
    for (int i = 0; i < filas_inimigos; i++)
    {
        for (int j = 0; j < TOTAL_INIMIGOS_POR_FILA; j++)
        {
            inimigos[inimigo_contador].vida = 1;
            inimigos[inimigo_contador].pos_x = inimigo_x_inicial + (j * intervalo_inimigos);
            inimigos[inimigo_contador].pos_y = inimigo_y_inicial;
            inimigos[inimigo_contador].disparo = 0;
            inimigos[inimigo_contador].sprite = 'W';
            inimigo_contador++;
        }
        inimigo_y_inicial++;
    }
}

void carregar_game_over()
{
    char menu_gameOver[12][43] = {
        "                 GAME OVER                 ",
        "+ - - - - - - - - - - - - - - - - - - - - +",
        "|                                         |",
        "|     HIGH_SCORE:          SCORE:         |",
        "|     XXX                  XXX            |",
        "|  *                                      |",
        "|           >> JOGAR NOVAMENTE         *  |",
        "|                                         |",
        "|              MENU                       |",
        "|     *                                   |",
        "|              QUIT                       |",
        "+ - - - - - - - - - - - - - - - - - - - - +"};

    while (1)
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 43; j++)
            {
                printf("%c", menu_gameOver[i][j]);
            }
            printf("\n");
        }
        scanf("%d");
    }
}

void controlar_jogador()
{
    char keyPress;

    // Verifica se uma tecla foi pressionada
    if (kbhit())
    {
        keyPress = getch();
    }
    else
    {
        keyPress = ' ';
    }

    if (keyPress == 'a' || keyPress == 'A')
    {
        if (jogador.pos_x > 1)
        {
            jogador.pos_x -= 1;
        }
    }

    if (keyPress == 'w' || keyPress == 'W')
    {
        if (jogador.disparo == 0)
        {
            jogador.disparo = 1;
            projetil.pos_x = jogador.pos_x;
            projetil.pos_y = jogador.pos_y - 1;
        }
    }

    if (keyPress == 'd' || keyPress == 'D')
    {
        if (jogador.pos_x < LARGURA - 2)
        {
            jogador.pos_x += 1;
        }
    }

    // criei para testar a tela de game over, caso o player digitar p ou P ele quita da partida
    if (keyPress == 'p' || keyPress == 'P')
    {
        jogador.vidas = 0;
    }
}

int intervalo_de_movimento = 0;
int deslocamento_inimigo = 1;
void desenhar_tela()
{
    // Limpar o buffer de console preenchendo-o com espaços vazios
    // Este loop varre todas as posições do buffer (LARGURA * ALTURA) e coloca ' '
    // Isso evita "resíduos" de quadros anteriores no console
    for (int i = 0; i < LARGURA * ALTURA; ++i)
    {
        bufferConsole[i].Char.AsciiChar = ESPACO_VAZIO;                                    // Preenche com espaços
        bufferConsole[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED; // Define cor padrão
    }

    // Imprime o jogador na tela
    int indice = jogador.pos_y * LARGURA + jogador.pos_x;
    bufferConsole[indice].Char.AsciiChar = jogador.sprite;

    for (int index = 0; index < TOTAL_INIMIGOS; index++)
    {
        if (projetil.pos_y == inimigos[index].pos_y && projetil.pos_x == inimigos[index].pos_x && inimigos[index].vida > 0) {
            jogador.disparo = 0;
            inimigos[index].vida--;
        }

        if (inimigos[index].vida != 0)
        {
            int indice = inimigos[index].pos_y * LARGURA + inimigos[index].pos_x;
            bufferConsole[indice].Char.AsciiChar = inimigos[index].sprite;
        }

        if (intervalo_de_movimento == 5)
        {
            if (inimigos[TOTAL_INIMIGOS - 1].pos_x >= LARGURA - 2)
            {
                deslocamento_inimigo *= -1;
                // inimigos[index].pos_y++;
            }
            // inimigos[index].pos_x += deslocamento_inimigo;
        }
    }

    if (jogador.disparo == 1)
    {

        int indice = projetil.pos_y * LARGURA + projetil.pos_x;
        bufferConsole[indice].Char.AsciiChar = projetil.sprite;
        projetil.pos_y -= 1;

        if (projetil.pos_y == 0)
        {
            jogador.disparo = 0;
        }
    }

    for (int i = 0; i < ALTURA; i++)
    {
        for (int j = 0; j < LARGURA; j++)
        {

            if (i == 0 || j == 0 || i == ALTURA - 1 || j == LARGURA - 1)
            {
                if (j == 0 || j % 2 == 0)
                {
                    // Imprime as bordas da tela
                    int indice = i * LARGURA + j;
                    bufferConsole[indice].Char.AsciiChar = '*';
                }
            }
        }
    }
    if (intervalo_de_movimento == 5)
    {
        intervalo_de_movimento = 0;
    }
    else
    {
        intervalo_de_movimento++;
    }
    WriteConsoleOutputA(console, bufferConsole, tamanhoBuffer, posicaoCaractere, &areaEscritaConsole);
}

// função que vai gerar... game over
void gerar_gameOver()
{
    if (jogador.vidas == 0)
    {
        jogo.game_over = 1;
    }
}

// jogar tudo na função principal

int main()
{

    carregar_menu_jogo();
    carregar_config_jogo();
    carregar_config_jogador();
    carregar_config_projetil();
    carregar_config_inimigo();

    console = GetStdHandle(STD_OUTPUT_HANDLE);

    while (1)
    {
        if (jogador.vidas == 0)
        {
            gerar_gameOver();
            carregar_game_over();
        }
        desenhar_tela();
        controlar_jogador();
        Sleep(ATRASO_TIQUE);
    }

    return 0;
}
