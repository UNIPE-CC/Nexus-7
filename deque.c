/* ------------------------------------------------------------------ */
/*  Deque Dinamico — Central de Suprimentos                           */
/* ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"

typedef struct NoDeque {
    char           item[80];
    int            prioridade;
    struct NoDeque* prox;
    struct NoDeque* ant;
} NoDeque;

typedef struct {
    NoDeque* frente;
    NoDeque* cauda;
    int      tamanho;
} DequeSuprimentos;


void inserirFrenteDeque(DequeSuprimentos* D, const char* item, int prio) {
    NoDeque* novo = (NoDeque*) malloc(sizeof(NoDeque));
    if (!novo) return;
    strncpy(novo->item, item, 79);
    novo->prioridade = prio;
    novo->ant  = NULL;
    novo->prox = D->frente;
    if (D->frente) D->frente->ant = novo;
    else           D->cauda = novo;
    D->frente  = novo;
    D->tamanho++;
}

void inserirFundoDeque(DequeSuprimentos* D, const char* item, int prio) {
    NoDeque* novo = (NoDeque*) malloc(sizeof(NoDeque));
    if (!novo) return;
    strncpy(novo->item, item, 79);
    novo->item[79] = '\0';
    novo->prioridade = prio;
    novo->prox = NULL;
    novo->ant  = D->cauda;
    if (D->cauda) {
        D->cauda->prox = novo;
    }else
        D->frente = novo;

    D->cauda = novo;
    D->tamanho++;
}

void imprimirDeque(DequeSuprimentos* D) {
    NoDeque* atual = D->frente;
    printf("\n=== CENTRAL DE SUPRIMENTOS ===\n");
    if (!atual) { printf("(sem pedidos)\n"); return; }
    while (atual) {
        printf("[P%d] %s\n", atual->prioridade, atual->item);
        atual = atual->prox;
    }
}