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

void removerElemento(LISTA *lista, int indice) {
    if (lista->tamanhoAtual == 1)
        return;
    lista->tamanhoAtual--;
    lista->vetor[indice] = lista->vetor[lista->tamanhoAtual];
}