/* ------------------------------------------------------------------ */
/*  Pilha — Historico de Missoes                                       */
/* ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoPilha {
    char           descricao[100];
    int            duracao_h;
    struct NoPilha* prox;
} NoPilha;

typedef struct {
    NoPilha* topo;
    int      tamanho;
} PilhaMissoes;

void inicializarPilha(PilhaMissoes* P) {
    P->topo    = NULL;
    P->tamanho = 0;
}

void empilharMissao(PilhaMissoes* P, const char* desc, int horas) {
    NoPilha* novo = (NoPilha*) malloc(sizeof(NoPilha));
    if (!novo) { printf("Erro de alocacao.\n"); return; }
    strncpy(novo->descricao, desc, 99);
    novo->descricao[99] = '\0';
    novo->duracao_h = horas;
    novo->prox = P->topo;
    P->topo    = novo;
    P->tamanho++;
}

char* desempilharMissao(PilhaMissoes* P) {
    if (!P->topo) { printf("Historico vazio.\n"); return NULL; }
    NoPilha* temp = P->topo;
    P->topo       = temp->prox;
    char* resultado = temp->descricao;  /* aponta para dentro de temp */
    free(temp);                          /* libera temp */
    P->tamanho--;
    return resultado;                    /* retorna ponteiro para memoria liberada */
}