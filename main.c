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
} VETOR;

typedef struct {
    char caracter;
    char *cor;
} CARACTER;

typedef struct {
    VETOR cabeca;
    VETOR corpo[AREA_TELA - 1];
    VETOR movimento;
    int tamanhoCorpo;
    bool vivo;
} COBRINHA;

CARACTER CARACTER_COMIDA = {'@', COR_COMIDA};
CARACTER CARACTER_CORPO = {'o', COR_COBRA};
CARACTER CARACTER_CABECA = {'0', COR_COBRA};
CARACTER CARACTER_ESPACO = {' ', COR_NULA};

VETOR DIRECAO_ESQUERDA = {-1, 0};
VETOR DIRECAO_DIREITA = {1, 0};
VETOR DIRECAO_CIMA = {0, -1};
VETOR DIRECAO_BAIXO = {0, 1};

COBRINHA jogador;
VETOR comidas[QUANTIDADE_MAXIMA_COMIDAS];
int quantidadeDeComidas = 1;

CARACTER tabuleiro[ALTURA][LARGURA];

// cabeçalhos
void iniciarJogo();
void perderJogo();
void renderizarJogo();
void atualizarCorpo();

void lerEntradas();
void virarDireita();
void virarEsquerda();
void virarCima();
void virarBaixo();
void moverCobrinha();

void colocarCobrinha();
void colocarComida();
void colocarCaracter(CARACTER, VETOR);

void limparTabuleiro();
void mostrarTabuleiro();
void mostrarLinha();
void mostrarCaracter(CARACTER, char*);

void adicionarComida();
void sortearPosicaoComida(int);
void comerComida(int);

void calcularColisoes();
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
    jogador.movimento.x = -1;
    jogador.movimento.y = 0;
    jogador.tamanhoCorpo = 0;
    jogador.vivo = true;

    colocarCobrinha();

    for (int i = 0; i < quantidadeDeComidas; i++)
        sortearPosicaoComida(i);

}

void moverCobrinha() {
    atualizarCorpo();
    jogador.cabeca.x += jogador.movimento.x;
    jogador.cabeca.y += jogador.movimento.y;
}

void renderizarJogo() {
    moverCobrinha();

    calcularColisoes();

    system("clear" );

    limparTabuleiro();

    colocarCobrinha();
    colocarComida();

    mostrarTabuleiro();
}

void lerEntradas() {
    char entrada;
    entrada = getchar();

    switch (entrada) {
        case 'q':
            jogador.vivo = false;
            break;
        case 'a':
            virarEsquerda();
            break;
        case 'd':
            virarDireita();
            break;
        case 'w':
            virarCima();
            break;
        case 's':
            virarBaixo();
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
        perderJogo();

    if (colidiuComParedes())
        perderJogo();
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

void perderJogo() {
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
        colocarCaracter(CARACTER_COMIDA, comidas[i]);
}

void colocarCobrinha() {
    for (int i = 0; i < jogador.tamanhoCorpo; i++)
        colocarCaracter(CARACTER_CORPO, jogador.corpo[i]);

    colocarCaracter(CARACTER_CABECA, jogador.cabeca);
}

void colocarCaracter(CARACTER caracter, VETOR posicao) {
    if ((posicao.x >= 0 && posicao.x < LARGURA) && (posicao.y >= 0 && posicao.y < ALTURA))
        tabuleiro[posicao.y][posicao.x] = caracter;
}

void atualizarCorpo() {
    for (int i = jogador.tamanhoCorpo; i > 0; i--)
        jogador.corpo[i] = jogador.corpo[i - 1];

    jogador.corpo[0] = jogador.cabeca;
}

bool naoEstaMovendoPara(VETOR direcao) {
    return (jogador.movimento.x != direcao.x || jogador.movimento.y != direcao.y);
}

void virarDireita() {
    if (naoEstaMovendoPara(DIRECAO_ESQUERDA))
        jogador.movimento = DIRECAO_DIREITA;
}

void virarEsquerda() {
    if (naoEstaMovendoPara(DIRECAO_DIREITA))
        jogador.movimento = DIRECAO_ESQUERDA;
}

void virarCima() {
    if (naoEstaMovendoPara(DIRECAO_BAIXO))
        jogador.movimento = DIRECAO_CIMA;
}

void virarBaixo() {
    if (naoEstaMovendoPara(DIRECAO_CIMA))
        jogador.movimento = DIRECAO_BAIXO;
}

void limparTabuleiro() {
    for (int i = 0; i < ALTURA; i++)
        for (int j = 0; j < LARGURA; j++)
            tabuleiro[i][j] = CARACTER_ESPACO;
}

void mostrarTabuleiro() {
    CARACTER barraLateral = {'|', COR_INTERFACE};

    mostrarLinha();

    for (int i = 0; i < ALTURA; i++) {
        mostrarCaracter(barraLateral, " ");

        for (int j = 0; j < LARGURA; j++) {
            mostrarCaracter(tabuleiro[i][j], " ");
        }

        mostrarCaracter(barraLateral, "\n");
    }

    mostrarLinha();
}

void mostrarLinha() {
    CARACTER mais = {'+', COR_INTERFACE};
    CARACTER menos = {'-', COR_INTERFACE};

    mostrarCaracter(mais, "");

    for (int i = 0; i < LARGURA * 2 + 1; i++)
        mostrarCaracter(menos, "");

    mostrarCaracter(mais, "\n");
}

void mostrarCaracter(CARACTER caracter, char *posfixo) {
    printf("%s%c%s%s", caracter.cor, caracter.caracter, posfixo, RESETAR_COR);
}
