// -- inclusão das bibliotecas a serem utilizadas -- //
#include <stdio.h>
#include <conio.h>   // --> funções para manipulação de entrada/saída do console (como ler teclas pressionadas diretamente do teclado).
#include <stdlib.h>  // --> funções úteis para a alocação de memória, controle de processos, conversão de tipos e outras operações gerais.
#include <windows.h> // --> desenvolvimento de aplicações que interagem com o sistema operacional Windows.
#include <time.h>    // --> utiliza mecanismos para usar o tempo local do dispositivo

// ---- definição das constantes do codigo ---- //
#define ALTURA 30
#define LARGURA 99
#define FILEIRAS_DE_INIMIGOS 3
#define TOTAL_INIMIGOS_POR_FILA 11
#define TOTAL_INIMIGOS 33
#define INTERVALO_INIMIGOS 2
#define ESPACO_VAZIO ' '
#define ATRASO_TIQUE 10

// --------- Criar as estrutras -------- //
typedef struct // --> estruturas para criar e manipular variáveis de maneira mais concisa, tornando o código mais legível e fácil de usar.
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
    int velocidade;
    int contador;
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
Projetil projetilInimigo;
Inimigo inimigos[TOTAL_INIMIGOS];
// ----------- PARTE DO PROFESSOR --------------- //
// Buffer: Um array de caracteres onde a string formatada será armazenada//
HANDLE console;                            // --> ex.: leitura de entrada diretamente do console, tem como objetivo fazer referência a objetos do sistema, como janelas, arquivos, e consoles
CHAR_INFO bufferConsole[LARGURA * ALTURA]; // --> manipulação de consoles, especificamente para operações de leitura e escrita em buffers de console
COORD tamanhoBuffer = {LARGURA, ALTURA};   // --> representar coordenadas de console, especialmente quando você precisa especificar uma posição em uma tela de console.
COORD posicaoCaractere = {0, 0};
SMALL_RECT areaEscritaConsole = {0, 0, LARGURA - 1, ALTURA - 1}; // --> definir e manipular pequenas áreas retangulares, especialmente na programação de consoles.

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
    projetil.velocidade = 1;
    projetil.contador = 0;
    projetil.sprite = '^';
}
void carregar_config_projetil_inimigo()
{
    projetilInimigo.pos_x = 999;
    projetilInimigo.pos_y = 999;
    projetilInimigo.velocidade = 2;
    projetilInimigo.contador = 0;
    projetilInimigo.sprite = 'v';
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
        "|      *                                  |",
        "|            >> NEW GAME            +     |",
        "|  *                                      |",
        "|      .                     *            |",
        "|               COMO JOGAR         .      |",
        "|                  +                      |",
        "|       *                    .            |",
        "|               QUIT                  *   |",
        "+ - - - - - - - - - - - - - - - - - - - - +"};

    while (1)
    {
        system("CLS"); // --> limpar o terminal, para retirar residuos desnecessarios
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 43; j++)
            {
                printf("%c", menu[i][j]);
            }
            printf("\n");
        }

        escolha = getch(); // --> 'lê um caractere diretamente do console sem a necessidade de usar o enter'

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

                menu[6][13] = '>';
                menu[6][14] = '>';
            }

            else if (menu[6][13] == '>')
            {
                menu[6][13] = ' ';
                menu[6][14] = ' ';

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

                menu[6][13] = '>';
                menu[6][14] = '>';
            }

            else if (menu[6][13] == '>')
            {
                menu[6][13] = ' ';
                menu[6][14] = ' ';

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

            else if (menu[6][13] == '>')
            {
                system("CLS");
                char comoJogar[27][43] = {
                    "               SPACE_INVADERS              ",
                    "+ - - - - - - - - - - - - - - - - - - - - +",
                    "|       Movimentacao do Personagem    +   |",
                    "|            *                            |",
                    "|     Tecla 'A'      e      Tecla 'D'     |",
                    "| move para esquerda |  move para direita |",
                    "|                    :                    |",
                    "|     Tecla 'W'      |  *    Tecla 'P'    |",
                    "|  efetua o disparo  :    sai da partida  |",
                    "|                                     *   |",
                    "| +  Caracteristicas da Personagem/Jogo   |",
                    "|                              *          |",
                    "|   *          Vida no Jogo               |",
                    "|                                         |",
                    "|    Nave aliada     |    Nave inimiga    |",
                    "|    VIDAS = 3       :  * VIDA = 1        |",
                    "|    *                                    |",
                    "|   Cada disparo acertado (tanto aliado   |",
                    "|    quanto inimigo) retiram 1 de vida    |",
                    "|                                  +      |",
                    "|            Objetivo do Jogo             |",
                    "|  *                                      |",
                    "|  Eliminar todas as naves inimigas sem   |",
                    "|     deixarem elas chegarem perto da     |",
                    "|          sua nave ou que elas   *       |",
                    "|       retirem todas as suas vidas       |",
                    "+ - - - - - - - - - - - - - - - - - - - - +"};
                int c = 0;
                while (c < 25)
                {
                    system("CLS");
                    for (int x = 0; x < 27; x++)
                    {
                        for (int y = 0; y < 43; y++)
                        {
                            printf("%c", comoJogar[x][y]);
                        }
                        printf("\n");
                        c++;
                    }
                }
                escolha = getch();
            }

            else if (menu[9][13] == '>')
            {
                exit(1); // --> função o qual encerra o programa;
            }
        }

        escolha = ' ';
    }
}

void carregar_config_inimigo()
{

    int filas_inimigos = 3;

    int intervalo_inimigos = INTERVALO_INIMIGOS; // = 2;

    // Centraliza os inimigos
    int inimigo_x_inicial = (LARGURA - (TOTAL_INIMIGOS_POR_FILA - 1) * intervalo_inimigos) / 2; // expressão matematica para centralizar os inimigos
    int inimigo_y_inicial = 3;
    // colocar os inimigos e tmb vericação dos status de cada
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

int carregar_game_over()
{
    char escolha = ' ';
    char menu_gameOver[12][43] = {
        "                 GAME OVER                 ",
        "+ - - - - - - - - - - - - - - - - - - - - +",
        "|                                         |",
        "|     HIGH_SCORE:          SCORE:         |",
        "|                                         |",
        "|  *                                      |",
        "|           >> JOGAR NOVAMENTE         *  |",
        "|                                         |",
        "|              MENU                       |",
        "|     *                                   |",
        "|              QUIT                       |",
        "+ - - - - - - - - - - - - - - - - - - - - +"};

    char caractere[4];
    char hi_score[4];

    snprintf(caractere, sizeof(caractere), "%d", jogo.score); // --> usada para formatar uma string e armazená-la em um buffer, garantindo que a escrita não ultrapasse o tamanho do buffer
    snprintf(hi_score, sizeof(hi_score), "%d", jogo.hi_score);

    // FUNÇÕES PARA O HI_SCORE
    if (jogo.hi_score == 0)
    {
        menu_gameOver[4][6] = '0';
        menu_gameOver[4][7] = '0';
        menu_gameOver[4][8] = '0';
    }
    else if (jogo.hi_score < 10)
    {
        menu_gameOver[4][8] = hi_score[0];
        menu_gameOver[4][7] = '0';
        menu_gameOver[4][6] = '0';
    }
    else if (jogo.hi_score >= 10 && jogo.hi_score < 100)
    {
        menu_gameOver[4][8] = hi_score[0];
        menu_gameOver[4][7] = hi_score[1];
        menu_gameOver[4][6] = '0';
    }

    else if (jogo.hi_score >= 100 && jogo.hi_score < 1000)
    {
        menu_gameOver[4][8] = hi_score[0];
        menu_gameOver[4][7] = hi_score[1];
        menu_gameOver[4][6] = hi_score[2];
    }

    // FUNÇÕES PARA O SCORE
    if (jogo.score == 0)
    {
        menu_gameOver[4][27] = '0';
        menu_gameOver[4][28] = '0';
        menu_gameOver[4][29] = '0';
    }
    else if (jogo.score < 10)
    {
        menu_gameOver[4][29] = caractere[0];
        menu_gameOver[4][28] = '0';
        menu_gameOver[4][27] = '0';
    }
    else if (jogo.score >= 10 && jogo.score < 100)
    {
        menu_gameOver[4][29] = caractere[0];
        menu_gameOver[4][28] = caractere[1];
        menu_gameOver[4][27] = '0';
    }

    else if (jogo.score >= 100 && jogo.score < 1000)
    {
        menu_gameOver[4][29] = caractere[0];
        menu_gameOver[4][28] = caractere[1];
        menu_gameOver[4][27] = caractere[2];
    }

    while (1)
    {
        system("CLS");
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 43; j++)
            {
                printf("%c", menu_gameOver[i][j]);
            }
            printf("\n");
        }

        escolha = getch();

        if (escolha == 'w' || escolha == 'W')
        {
            // Jogar novamente
            if (menu_gameOver[6][13] == '>')
            {
                menu_gameOver[6][12] = ' ';
                menu_gameOver[6][13] = ' ';

                menu_gameOver[10][12] = '>';
                menu_gameOver[10][13] = '>';
            }

            // menu
            else if (menu_gameOver[10][13] == '>')
            {
                menu_gameOver[10][12] = ' ';
                menu_gameOver[10][13] = ' ';

                menu_gameOver[8][12] = '>';
                menu_gameOver[8][13] = '>';
            }

            // quit
            else if (menu_gameOver[8][13] == '>')
            {
                menu_gameOver[8][12] = ' ';
                menu_gameOver[8][13] = ' ';

                menu_gameOver[6][12] = '>';
                menu_gameOver[6][13] = '>';
            }
        }

        else if (escolha == 's' || escolha == 'S')
        {
            // Jogar novamente
            if (menu_gameOver[6][13] == '>')
            {
                menu_gameOver[6][12] = ' ';
                menu_gameOver[6][13] = ' ';

                menu_gameOver[8][12] = '>';
                menu_gameOver[8][13] = '>';
            }

            // MEU
            else if (menu_gameOver[8][13] == '>')
            {
                menu_gameOver[8][12] = ' ';
                menu_gameOver[8][13] = ' ';

                menu_gameOver[10][12] = '>';
                menu_gameOver[10][13] = '>';
            }

            // QUIT
            else if (menu_gameOver[10][13] == '>')
            {
                menu_gameOver[10][12] = ' ';
                menu_gameOver[10][13] = ' ';

                menu_gameOver[6][12] = '>';
                menu_gameOver[6][13] = '>';
            }
        }

        else if (escolha == 'e' || escolha == 'E')
        {
            // SELECIONANDO QUIT
            if (menu_gameOver[10][13] == '>')
            {
                exit(1);
            }

            // SELECIONAR JOGAR NOVAMENTE
            else if (menu_gameOver[6][13] == '>')
            {
                jogo.game_over = 0;
                carregar_config_jogador();
                carregar_config_projetil();
                carregar_config_inimigo();
                return 0;
            }

            // SELECIONAR MENU
            else if (menu_gameOver[8][13] == '>')
            {
                jogo.game_over = 0;
                return 1;
            }

            //
        }

        escolha = ' ';
    }
}

void controlar_jogador()
{
    char keyPress;

    // Verifica se uma tecla foi pressionada
    if (kbhit()) // --> detectar se uma tecla foi pressionada
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

// ---------- função para o disparo do inimigo ------------ //
int intervalo_de_movimento = 0;
int deslocamento_inimigo = 1;
int disparoInimigo = 0;
void atirar_o_projetil_inimigo()
{
    if (disparoInimigo == 1)
        return;

    int coluna_escolhida, inimigo_disparador = -1;
    int inimigo_x_inicial = (LARGURA - (TOTAL_INIMIGOS_POR_FILA - 1) * INTERVALO_INIMIGOS) / 2;

    int tentativas = 0; // Contador de tentativas para evitar loop infinito

    // Loop que irá selecionar um inimigo para disparar o próximo tiro.
    /* Para que seja escolhido sempre um inimigo que está na frente
    (evitando assim que o disparo atravesse algum inimigo) será escolhido uma coluna aleatóriamente e depois,
    começando da fileira da frente, irá verificar se o inimigo está vivo.
    Caso o inimigo esteja morto, irá verificar se o inimigo de trás (na mesma coluna) está vivo,
    e fará isso até verificar todas as fileiras da mesma coluna.
    Caso a coluna não tenha inimigos vivos, outra coluna aleatória será escolhida,
    e assim até que um inimigo seja escolhido.
    */
    while (inimigo_disparador == -1 && tentativas < 5)
    {
        coluna_escolhida = rand() % TOTAL_INIMIGOS_POR_FILA;
        int coluna_x = (coluna_escolhida * INTERVALO_INIMIGOS) + inimigo_x_inicial;

        for (int linha = 0; linha < FILEIRAS_DE_INIMIGOS; linha++)
        {
            // Aqui, calculamos o índice do inimigo com a lógica correta
            int inimigo_index = (FILEIRAS_DE_INIMIGOS - 1 - linha) * TOTAL_INIMIGOS_POR_FILA + coluna_escolhida;

            if (inimigos[inimigo_index].vida > 0)
            {
                inimigo_disparador = inimigo_index;
                break;
            }
        }
        tentativas++;
    }

    // Se não encontrou um inimigo, tenta sequencialmente
    if (inimigo_disparador == -1)
    {
        for (int i = 0; i < TOTAL_INIMIGOS; i++)
        {
            if (inimigos[i].vida > 0)
            {
                inimigo_disparador = i;
                break;
            }
        }
    }

    // Se encontrou um inimigo para disparar
    if (inimigo_disparador != -1)
    {
        projetilInimigo.pos_x = inimigos[inimigo_disparador].pos_x;
        projetilInimigo.pos_y = inimigos[inimigo_disparador].pos_y + 1;
        disparoInimigo = 1;
    }
}

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

    // ----- Exibir Score e Vidas no topo da tela ----- //
    int margem_do_texto = 5; // Valor usado para dar espaçamento do texto
    char scoreTexto[30];
    sprintf(scoreTexto, "SCORE: %d", jogo.score); // o sprintf --> é usada para formatar e armazenar uma string em um buffer
    for (int i = 0; scoreTexto[i] != '\0'; ++i)
    {
        int indice = 2 * LARGURA + (i + margem_do_texto); // --> posicionamento do score
        bufferConsole[indice].Char.AsciiChar = scoreTexto[i];
    }

    char vidasTexto[20];
    sprintf(vidasTexto, "LIVES: %d", jogador.vidas);
    int posInicioVidas = (LARGURA - margem_do_texto) - strlen(vidasTexto); // -->usada para determinar o comprimento de uma string, excluindo o caractere nulo ('\0') que termina a string.
    for (int i = 0; vidasTexto[i] != '\0'; ++i)
    {
        int indice = 2 * LARGURA + (posInicioVidas + i);
        bufferConsole[indice].Char.AsciiChar = vidasTexto[i];
    }
    // Imprime o jogador na tela
    int indice = jogador.pos_y * LARGURA + jogador.pos_x;
    bufferConsole[indice].Char.AsciiChar = jogador.sprite;

    // Atualiza a posição dos inimigos
    for (int index = 0; index < TOTAL_INIMIGOS; index++)
    {
        if (projetil.pos_y == inimigos[index].pos_y && projetil.pos_x == inimigos[index].pos_x && inimigos[index].vida > 0)
        {
            jogador.disparo = 0;
            inimigos[index].vida--;
            jogo.score += 1;
            projetil.pos_x = 999;
            projetil.pos_y = 999;

            if (jogo.score > jogo.hi_score)
            {
                jogo.hi_score = jogo.score;
            }
        }

        if (inimigos[index].vida != 0)
        {
            int indice = inimigos[index].pos_y * LARGURA + inimigos[index].pos_x;
            bufferConsole[indice].Char.AsciiChar = inimigos[index].sprite;
        }

        if (intervalo_de_movimento >= 7)
        {

            if (inimigos[TOTAL_INIMIGOS - 1].pos_y == jogador.pos_y - 1) // caso os inimigos cheguem perto do player, para encerrar o programa
            {
                jogador.vidas = 0;
                break;
            }
            if (inimigos[TOTAL_INIMIGOS - 1].pos_x == LARGURA - 2)
            {
                inimigos[index].pos_y++;
            }

            if (inimigos[0].pos_x == 1)
            {
                inimigos[index].pos_y++;
            }

            inimigos[index].pos_x += deslocamento_inimigo;
        }
    }
    // Atualiza a posição do projetil do jogador
    if (jogador.disparo == 1)
    {

        int indice = projetil.pos_y * LARGURA + projetil.pos_x;
        bufferConsole[indice].Char.AsciiChar = projetil.sprite;
        if (projetil.contador >= projetil.velocidade)
        {
            projetil.pos_y -= 1;
            projetil.contador = 0;
            if (projetil.pos_y == 0)
            {
                jogador.disparo = 0;
            }
        }
        else
        {
            projetil.contador++;
        }
    }

    // Atualiza a posição do projetil do Inimigo
    if (disparoInimigo == 1)
    {
        int indice = projetilInimigo.pos_y * LARGURA + projetilInimigo.pos_x;
        bufferConsole[indice].Char.AsciiChar = projetilInimigo.sprite;

        if (projetilInimigo.contador >= projetilInimigo.velocidade)
        {
            projetilInimigo.pos_y += 1;
            projetilInimigo.contador = 0;

            if (projetilInimigo.pos_y >= ALTURA - 2)
            {
                disparoInimigo = 0;
            }

            else if (projetilInimigo.pos_y == jogador.pos_y && projetilInimigo.pos_x == jogador.pos_x)
            {
                disparoInimigo = 0;
                jogador.vidas--;
            }
        }
        else
        {
            projetilInimigo.contador++;
        }
    }
    else
    {

        atirar_o_projetil_inimigo();
    }

    // Cria as bordas do mapa
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

    WriteConsoleOutputA(console, bufferConsole, tamanhoBuffer, posicaoCaractere, &areaEscritaConsole); // -->é usada para escrever um bloco de caracteres e seus atributos em um buffer de console.
    if (intervalo_de_movimento >= 7)
    {
        if (inimigos[TOTAL_INIMIGOS - 1].pos_x >= LARGURA - 2)
        {
            deslocamento_inimigo = deslocamento_inimigo * -1;
        }
        else if (inimigos[0].pos_x <= 1)
        {
            deslocamento_inimigo = deslocamento_inimigo * -1;
        }
        intervalo_de_movimento = 0;
    }
    else
    {
        intervalo_de_movimento++;
    }
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
    console = GetStdHandle(STD_OUTPUT_HANDLE); // --> Usado para obter o handle da saída padrão do console. Este handle pode ser usado para escrever no console.
    carregar_config_jogo();
    carregar_config_projetil_inimigo();

    // Serve para que possa ser criado números aleatórios, que são usados para selecionar qual inimigo irá atirar

    srand(time(NULL)); // --> inicializa o gerador de números aleatórios usando o tempo atual como semente, garantindo realmente que os numeros vão ser aleatorios
    while (1)
    {
        carregar_menu_jogo();
        carregar_config_jogador();
        carregar_config_projetil();
        carregar_config_inimigo();

        while (1)
        {
            if (jogador.vidas == 0 || jogo.score == TOTAL_INIMIGOS)
            {
                gerar_gameOver();
                int seila = carregar_game_over();

                // função para jogar novamente
                if (seila == 0)
                {
                    system("CLS");
                    carregar_config_inimigo();
                    carregar_config_jogador();
                    carregar_config_projetil();

                    jogo.score = 0;
                }

                // função para retornar para o Menu
                else if (seila == 1)
                {
                    jogo.score = 0;

                    break;
                }
            }
            desenhar_tela();
            controlar_jogador();
            Sleep(ATRASO_TIQUE);
        }
    }

    return 0;
}
