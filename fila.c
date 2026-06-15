/* ------------------------------------------------------------------ */
/*  Fila Estatica Circular — Camara de Descompressao (Airlock)        */
/* ------------------------------------------------------------------ */

#include <stdio.h>
#include "tad.h"

typedef struct {
    Tripulante dados[MAX_AIRLOCK];
    int        inicio;
    int        fim;
    int        tamanho;
} FilaAirlock;

void inicializarFilaAirlock(FilaAirlock* F) {
    F->inicio  = 0;
    F->fim     = 0;
    F->tamanho = 0;
}

int enfileirarAirlock(FilaAirlock* F, Tripulante t) {
    if (F->tamanho >= MAX_AIRLOCK){
        printf("Airlock cheio. Capacidade maxima: %d tripulantes.\n", MAX_AIRLOCK);
        return 0;
    }
    F->dados[F->fim] = t;
    F->fim           = (F->fim + 1) % MAX_AIRLOCK;
    F->tamanho++;
    return 1;
}

int desenfileirarAirlock(FilaAirlock* F, Tripulante* t) {
    if (F->tamanho == 0) { printf("Airlock vazio.\n"); return 0; }
    *t       = F->dados[F->inicio];
    F->inicio = (F->inicio + 1) % MAX_AIRLOCK;
    F->tamanho--;
    return 1;
}