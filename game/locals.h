#ifndef JOGO_DA_COBRINHA_ED_LOCALS_H
#define JOGO_DA_COBRINHA_ED_LOCALS_H

#include "lista.h"

#define LARGURA_CENARIO 17
#define ALTURA_CENARIO 11
#define TAMANHO_MAXIMO_COBRINHA (ALTURA_CENARIO * LARGURA_CENARIO)
#define TAMANHO_INICIAL_COBRINHA 3

#define COR_NULA ""
#define COR_INTERFACE "\x1b[1;37m"
#define COR_COMIDA "\x1b[1;31m"
#define COR_COBRA "\x1b[1;32m"
#define RESETAR_COR "\x1b[1;0m"

typedef int BOOL;
#define true 1
#define false 0

typedef PONTO DIRECAO;

typedef struct {
    char caracter;
    char *cor;
} CARACTER;

static CARACTER COMIDA = {'@', COR_COMIDA};
static CARACTER CORPO = {'o', COR_COBRA};
static CARACTER CABECA = {'0', COR_COBRA};
static CARACTER ESPACO = {' ', COR_NULA};
static CARACTER BORDA = {'+', COR_INTERFACE};
static CARACTER LINHA_HORIZONTAL = {'-', COR_INTERFACE};
static CARACTER LINHA_VERTICAL = {'|', COR_INTERFACE};

static DIRECAO ESQUERDA = {-1, 0};
static DIRECAO DIREITA = {1, 0};
static DIRECAO CIMA = {0, -1};
static DIRECAO BAIXO = {0, 1};
static PONTO POSICAO_INICIAL = {LARGURA_CENARIO / 2 + TAMANHO_INICIAL_COBRINHA, ALTURA_CENARIO / 2};

#endif //JOGO_DA_COBRINHA_ED_LOCALS_H
