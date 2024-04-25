#ifndef JOGO_DA_COBRINHA_ED_GAME_H
#define JOGO_DA_COBRINHA_ED_GAME_H

#include "locals.h"

// cabeçalhos
void rodar();
void perderJogo();
void ganharJogo();
void renderizarJogo();

void lerEntradas();
void virarDireita();
void virarEsquerda();
void virarCima();
void virarBaixo();
void moverCobrinha();

void colocarCobrinha();
void colocarComidas();
void colocarCaracter(CARACTER, PONTO);

void limparCenario();
void mostrarCenario();
void mostrarLinha();
void mostrarCaracter(CARACTER, char*);

PONTO sortearPosicao();
void comerComida(int);

void calcularColisoes();
BOOL colidiuComComida(int);
BOOL colidiuComCorpo();
BOOL colidiuComParedes();

#endif // JOGO_DA_COBRINHA_ED_GAME_H
