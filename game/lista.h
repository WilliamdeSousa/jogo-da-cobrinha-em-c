#ifndef JOGO_DA_COBRINHA_ED_LISTA_H
#define JOGO_DA_COBRINHA_ED_LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} PONTO;

typedef struct {
    PONTO *vetor;
    int tamanhoAtual, tamanhoMaximo;
} LISTA;

LISTA criarLista(int, int);
void adicionarElemento(LISTA *, PONTO);
void removerElemento(LISTA *, int);

#endif // JOGO_DA_COBRINHA_ED_LISTA_H
