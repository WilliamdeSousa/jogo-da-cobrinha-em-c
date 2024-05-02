#include "lista.h"

LISTA criarLista(int tamanhoInicial, int tamanhoMaximo) {
    LISTA lista;
    lista.vetor = malloc(sizeof(PONTO) * tamanhoMaximo);
    lista.tamanhoAtual = tamanhoInicial;
    lista.tamanhoMaximo = tamanhoMaximo;
    return lista;
}

void adicionarElemento(LISTA *lista, PONTO ponto) {
    if (lista->tamanhoAtual < lista->tamanhoMaximo) {
        lista->vetor[lista->tamanhoAtual] = ponto;
        lista->tamanhoAtual++;
    }
}