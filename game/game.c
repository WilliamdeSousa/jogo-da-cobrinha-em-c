#include "game.h"

// variaveis
LISTA cobrinha;
PONTO comida;
DIRECAO direcaoCobrinha;
BOOL cobrinhaViva;

CARACTER cenario[ALTURA_CENARIO][LARGURA_CENARIO];

// JOGO
void rodar() {
    // CONFIGURAÇÔES INICIAIS
    limparCenario();

    cobrinha = criarLista(TAMANHO_INICIAL_COBRINHA, TAMANHO_MAXIMO_COBRINHA);
    direcaoCobrinha = ESQUERDA;

    cobrinhaViva = true;

    cobrinha.vetor[0] = POSICAO_INICIAL;

    for (int i = 0; i < TAMANHO_INICIAL_COBRINHA; i++)
        moverCobrinha();

    colocarCobrinha();

    comida = sortearPosicao();

    while (cobrinhaViva) {
        renderizarJogo();

        lerEntradas();

        moverCobrinha();
    }
}

void renderizarJogo() {
    calcularColisoes();

    system("clear");

    limparCenario();

    colocarCobrinha();

    colocarComida();

    mostrarCenario();
}

void perderJogo() {
    printf("Você perdeu!\n");
    exit(0);
}

void ganharJogo() {
    printf("Parabéns! Você ganhou!!!\n");
    exit(0);
}

void lerEntradas() {
    char entrada;

    entrada = (char) getchar();

    if (entrada == '\n')
        entrada = ' ';
    else
        while (getchar() != '\n');

    switch (entrada) {
        case 'q':
            cobrinhaViva = false;
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
        default:
            break;
    }
}

void moverCobrinha() {
    for (int i = cobrinha.tamanhoAtual; i > 0; i--)
        cobrinha.vetor[i] = cobrinha.vetor[i - 1];

    cobrinha.vetor[0].x += direcaoCobrinha.x;
    cobrinha.vetor[0].y += direcaoCobrinha.y;
}

void calcularColisoes() {
    if (colidiuComCorpo() || colidiuComParedes())
        perderJogo();

    if (colidiuComComida())
        comerComida();
}

BOOL colidiuComCorpo() {
    return cenario[cobrinha.vetor[0].y][cobrinha.vetor[0].x].caracter == CORPO.caracter;
}


BOOL colidiuComParedes() {
    return (
            cobrinha.vetor[0].x < 0 || cobrinha.vetor[0].y < 0 ||
            cobrinha.vetor[0].y >= ALTURA_CENARIO || cobrinha.vetor[0].x >= LARGURA_CENARIO
    );
}

BOOL colidiuComComida() {
    return cobrinha.vetor[0].x == comida.x && cobrinha.vetor[0].y == comida.y;
}

void comerComida() {
    adicionarElemento(&cobrinha, cobrinha.vetor[cobrinha.tamanhoAtual]);

    if (cobrinha.tamanhoAtual == cobrinha.tamanhoMaximo)
        ganharJogo();

    comida = sortearPosicao();
}

PONTO sortearPosicao() {
    PONTO ponto;
    srand(time(NULL));

    do {
        ponto.x = rand() % LARGURA_CENARIO;
        ponto.y = rand() % ALTURA_CENARIO;
    } while (cenario[ponto.y][ponto.x].caracter != ESPACO.caracter);

    return ponto;
}

// CENARIO
void limparCenario() {
    for (int i = 0; i < ALTURA_CENARIO; i++)
        for (int j = 0; j < LARGURA_CENARIO; j++)
            cenario[i][j] = ESPACO;
}

void colocarComida() {
    colocarCaracter(COMIDA, comida);
}

void colocarCobrinha() {
    colocarCaracter(CABECA, cobrinha.vetor[0]);

    for (int i = 1; i < cobrinha.tamanhoAtual; i++)
        colocarCaracter(CORPO, cobrinha.vetor[i]);
}

void colocarCaracter(CARACTER caracter, PONTO posicao) {
    cenario[posicao.y][posicao.x] = caracter;
}

// DIREÇÕES
BOOL naoEstaMovendoPara(DIRECAO direcao) {
    return (direcaoCobrinha.x != direcao.x || direcaoCobrinha.y != direcao.y);
}

void virarDireita() {
    if (naoEstaMovendoPara(ESQUERDA))
        direcaoCobrinha = DIREITA;
}

void virarEsquerda() {
    if (naoEstaMovendoPara(DIREITA))
        direcaoCobrinha = ESQUERDA;
}

void virarCima() {
    if (naoEstaMovendoPara(BAIXO))
        direcaoCobrinha = CIMA;
}

void virarBaixo() {
    if (naoEstaMovendoPara(CIMA))
        direcaoCobrinha = BAIXO;
}

// FORMATAÇÃO
void mostrarLinha() {
    mostrarCaracter(BORDA, "");

    for (int i = 0; i < LARGURA_CENARIO * 2 + 1; i++)
        mostrarCaracter(LINHA_HORIZONTAL, "");

    mostrarCaracter(BORDA, "\n");
}

void mostrarCaracter(CARACTER caracter, char *posfixo) {
    printf("%s%c%s%s", caracter.cor, caracter.caracter, posfixo, RESETAR_COR);
}

void mostrarCenario() {
    mostrarLinha();

    for (int i = 0; i < ALTURA_CENARIO; i++) {
        mostrarCaracter(LINHA_VERTICAL, " ");

        for (int j = 0; j < LARGURA_CENARIO; j++) {
            mostrarCaracter(cenario[i][j], " ");
        }

        mostrarCaracter(LINHA_VERTICAL, "\n");
    }

    mostrarLinha();
}
