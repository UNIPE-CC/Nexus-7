/* ------------------------------------------------------------------ */
/*  Lista Encadeada — Manifesto da Tripulacao                          */
/* ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"

typedef struct NoLista {
    Tripulante      dados;
    struct NoLista* prox;
} NoLista;

typedef struct {
    NoLista* cabeca;
    int      tamanho;
} ListaTripulacao;

void inicializarLista(ListaTripulacao* L) {
    L->cabeca  = NULL;
    L->tamanho = 0;
}

void inserirTripulante(ListaTripulacao* L, Tripulante t) {
    NoLista* novo = (NoLista*) malloc(sizeof(NoLista));
    if (!novo) { printf("Erro de alocacao.\n"); return; }
    novo->dados = t;
    novo->prox  = L->cabeca;
    L->cabeca = novo;
    L->tamanho++;
}

int removerTripulante(ListaTripulacao* L, int id) {
    NoLista* atual    = L->cabeca;
    NoLista* anterior = NULL;
    while (atual != NULL && atual->dados.id != id) {
        anterior = atual;
        atual    = atual->prox;
    }
    if (!atual) return 0;
    if (!anterior) L->cabeca    = atual->prox;
    else           
        anterior->prox = atual->prox;
    free(atual);
    L->tamanho--;
    return 1;
}

void imprimirManifesto(ListaTripulacao* L) {
    NoLista* atual = L->cabeca;
    printf("\n=== MANIFESTO DA TRIPULACAO ===\n");
    if (!atual) { printf("(vazio)\n"); return; }
    while (atual != NULL) {
        printf("ID %02d | %-20s | %-12s | O2: %5.1f%%\n",
               atual->dados.id,
               atual->dados.nome,
               atual->dados.especialidade,
               atual->dados.nivel_oxigenio);
        atual = atual->prox;
    }

    while (atual != NULL)
    {
        printf("ID %02d | %-20s | %-12s | O2: %5.1f%%\n",
               atual->dados.id,
               atual->dados.nome,
               atual->dados.especialidade,
               atual->dados.nivel_oxigenio);

        atual = atual->prox;
    }
}

float calcularMediaOxigenio(ListaTripulacao* L)
{
    if (L->cabeca == NULL)
    {
        printf("Lista vazia.\n");
        return 0.0f;
    }

    float soma = 0.0f;
    NoLista* atual = L->cabeca;

    while (atual != NULL)
    {
        soma += atual->dados.nivel_oxigenio;
        atual = atual->prox;
    }

    return soma / L->tamanho;
}