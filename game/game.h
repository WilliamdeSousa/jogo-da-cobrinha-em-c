#ifndef JOGO_DA_COBRINHA_ED_GAME_H
#define JOGO_DA_COBRINHA_ED_GAME_H

#include "locals.h"

// cabeçalhos
void rodar();
void ganharJogo();
void perderJogo();
void renderizarJogo();

void lerEntradas();
void virarDireita();
void virarEsquerda();
void virarCima();
void virarBaixo();
void moverCobrinha();

void colocarCobrinha();
void colocarComida();
void colocarCaracter(CARACTER, PONTO);

void limparCenario();
void mostrarCenario();
void mostrarLinha();
void mostrarCaracter(CARACTER, char*);

PONTO sortearPosicao();
void comerComida();

void calcularColisoes();
BOOL colidiuComComida();
BOOL colidiuComCorpo();
BOOL colidiuComParedes();

#endif // JOGO_DA_COBRINHA_ED_GAME_H
