#include <stdio.h>
#include <stdlib.h>

#define QUANTIDADE_MAXIMA_COMIDAS 5
#define LARGURA 25
#define ALTURA 15
#define AREA_TELA (ALTURA * LARGURA)

#define COR_NULA ""
#define COR_INTERFACE "\x1b[37;1m"
#define COR_COMIDA "\x1b[31m"
#define COR_COBRA "\x1b[32m"
#define RESETAR_COR "\x1b[0m"

#define true 1
#define false 0

typedef int bool;

typedef struct {
    int x;
    int y;
} POSICAO;

typedef struct {
    char caracter;
    char *cor;
} CARACTER;

typedef struct {
    POSICAO cabeca;
    POSICAO corpo[AREA_TELA - 1];
    int tamanhoCorpo;
    bool vivo;
} COBRINHA;

CARACTER CARACTER_COMIDA = {'@', COR_COMIDA};
CARACTER CARACTER_CORPO = {'o', COR_COBRA};
CARACTER CARACTER_CABECA = {'0', COR_COBRA};
CARACTER CARACTER_ESPACO = {' ', COR_NULA};

COBRINHA jogador;
POSICAO comidas[QUANTIDADE_MAXIMA_COMIDAS];
int quantidadeDeComidas = 1;

CARACTER tabuleiro[ALTURA][LARGURA];

// cabeçalhos
void iniciarJogo();
void renderizarJogo();
void lerEntradas();
void moverDireita();
void moverEsquerda();
void moverCima();
void moverBaixo();
void colocarCobrinha();
void colocarComida();
void colocarCharNoTabuleiro(CARACTER, POSICAO);
void limparTabuleiro();
void mostrarTabuleiro();
void linha();
void mostrar(CARACTER, char*);
void perder();
void adicionarComida();
void calcularColisoes();
void sortearPosicaoComida(int);
void comerComida(int);
bool colidiuComComida(int);
bool colidiuComCorpo();
bool colidiuComParedes();

int main() {
    iniciarJogo();

    while (jogador.vivo) {
        renderizarJogo();

        lerEntradas();
    }

    return 0;
}

void iniciarJogo() {
    limparTabuleiro();

    jogador.cabeca.x = LARGURA / 2;
    jogador.cabeca.y = ALTURA / 2;
    jogador.tamanhoCorpo = 0;
    jogador.vivo = true;

    colocarCobrinha();

    for (int i = 0; i < quantidadeDeComidas; i++)
        sortearPosicaoComida(i);

}

void renderizarJogo() {
    calcularColisoes();

    system("clear" );

    limparTabuleiro();

    colocarCobrinha();
    colocarComida();

    mostrarTabuleiro();
}

void lerEntradas() {
    char entrada;
    scanf(" %c", &entrada);

    switch (entrada) {
        case 'q':
            jogador.vivo = false;
            break;
        case 'a':
            moverEsquerda();
            break;
        case 'd':
            moverDireita();
            break;
        case 'w':
            moverCima();
            break;
        case 's':
            moverBaixo();
            break;
    }
}

void calcularColisoes() {
    for (int i = 0; i < quantidadeDeComidas; i++)
        if (colidiuComComida(i)) {
            comerComida(i);

            if (jogador.tamanhoCorpo % 5 == 0)
                adicionarComida();
        }

    if (colidiuComCorpo())
        perder();

    if (colidiuComParedes())
        perder();
}

bool colidiuComComida(int indice) {
    return (jogador.cabeca.y == comidas[indice].y && jogador.cabeca.x == comidas[indice].x);
}

bool colidiuComCorpo() {
    return (tabuleiro[jogador.cabeca.y][jogador.cabeca.x].caracter == CARACTER_CORPO.caracter);
}

bool colidiuComParedes() {
    return (
            jogador.cabeca.x < 0 || jogador.cabeca.y < 0 ||
            jogador.cabeca.y >= ALTURA || jogador.cabeca.x >= LARGURA
    );
}

void perder() {
    printf("GAME OVER!\n");
    jogador.vivo = false;
    exit(0);
}

void comerComida(int indice) {
    jogador.tamanhoCorpo++;
    sortearPosicaoComida(indice);
}

void adicionarComida() {
    if (quantidadeDeComidas < QUANTIDADE_MAXIMA_COMIDAS) {
        sortearPosicaoComida(quantidadeDeComidas);
        quantidadeDeComidas++;
    }
}

void sortearPosicaoComida(int indice) {
    int x, y;

    do {
        x = (rand() % LARGURA);
        y = (rand() % ALTURA);
    } while (tabuleiro[y][x].caracter != CARACTER_ESPACO.caracter);

    comidas[indice].x = x;
    comidas[indice].y = y;
}

void colocarComida() {
    for (int i = 0; i < quantidadeDeComidas; i++)
        colocarCharNoTabuleiro(CARACTER_COMIDA, comidas[i]);
}

void colocarCobrinha() {
    for (int i = 0; i < jogador.tamanhoCorpo; i++)
        colocarCharNoTabuleiro(CARACTER_CORPO, jogador.corpo[i]);

    colocarCharNoTabuleiro(CARACTER_CABECA, jogador.cabeca);
}

void colocarCharNoTabuleiro(CARACTER caracter, POSICAO posicao) {
    if ((posicao.x >= 0 && posicao.x < LARGURA) && (posicao.y >= 0 && posicao.y < ALTURA))
        tabuleiro[posicao.y][posicao.x] = caracter;
}

void atualizarCorpo() {
    for (int i = jogador.tamanhoCorpo; i > 0; i--)
        jogador.corpo[i] = jogador.corpo[i - 1];

    jogador.corpo[0] = jogador.cabeca;
}

void moverDireita() {
    atualizarCorpo();
    jogador.cabeca.x++;
}

void moverEsquerda() {
    atualizarCorpo();
    jogador.cabeca.x--;
}

void moverCima() {
    atualizarCorpo();
    jogador.cabeca.y--;
}

void moverBaixo() {
    atualizarCorpo();
    jogador.cabeca.y++;
}

void limparTabuleiro() {
    for (int i = 0; i < ALTURA; i++)
        for (int j = 0; j < LARGURA; j++)
            tabuleiro[i][j] = CARACTER_ESPACO;
}

void mostrarTabuleiro() {
    CARACTER barraLateral = {'|', COR_INTERFACE};

    linha();

    for (int i = 0; i < ALTURA; i++) {
        mostrar(barraLateral, " ");

        for (int j = 0; j < LARGURA; j++) {
            mostrar(tabuleiro[i][j], " ");
        }

        mostrar(barraLateral, "\n");
    }

    linha();
}

void linha() {
    CARACTER mais = {'+', COR_INTERFACE};
    CARACTER menos = {'-', COR_INTERFACE};

    mostrar(mais, "");

    for (int i = 0; i < LARGURA * 2 + 1; i++)
        mostrar(menos, "");

    mostrar(mais, "\n");
}

void mostrar(CARACTER caracter, char *posfixo) {
    printf("%s%c%s%s", caracter.cor, caracter.caracter, posfixo, RESETAR_COR);
}
