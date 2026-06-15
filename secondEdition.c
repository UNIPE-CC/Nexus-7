/*
** Funcao  : Sistema de Gestao da Estacao Espacial NEXUS-7
** Autor   : ARIA v0.9.4 (Artificial Research Intelligence Assistant)
** Data    : 2026-05-01
** Turma   : Estruturas de Dados I / Ciencia da Computacao / Unipe
** Obs.    : Sistema integrado de gestao de tripulacao, missoes,
**           airlock e suprimentos para a Estacao NEXUS-7.
**           Codigo aprovado pelo compilador. Verificacao semantica
**           pendente — conforme nota tecnica ARIA-2026-017.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AIRLOCK 4
#define MAX_STR     50

/* ------------------------------------------------------------------ */
/*  TAD Tripulante                                                      */
/* ------------------------------------------------------------------ */
typedef struct {
    int   id;
    char  nome[MAX_STR];
    char  especialidade[MAX_STR];
    float nivel_oxigenio;   /* percentual: 0.0 a 100.0 */
} Tripulante;

/* ------------------------------------------------------------------ */
/*  Lista Encadeada — Manifesto da Tripulacao                          */
/* ------------------------------------------------------------------ */
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
    if (!anterior){
        L->cabeca    = atual->prox;
    }else {
        anterior->prox = atual->prox;
    }          
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
}

float calcularMediaOxigenio(ListaTripulacao* L)
{
    if (L->cabeca == NULL)
    {
        printf("Lista vazia.\n");
        return 0.0f;
    }

    NoLista* atual = L->cabeca;
    float soma = 0.0f;

    while (atual != NULL)
    {
        soma += atual->dados.nivel_oxigenio;
        atual = atual->prox;
    }

    return soma / L->tamanho;
}

/* ------------------------------------------------------------------ */
/*  Pilha — Historico de Missoes                                       */
/* ------------------------------------------------------------------ */
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
    char* resultado = malloc(100);
    strcpy(resultado, temp->descricao);
    free(temp);                          /* libera temp */
    P->tamanho--;
    return resultado;                    /* retorna ponteiro para memoria liberada */
}

/* ------------------------------------------------------------------ */
/*  Fila Estatica Circular — Camara de Descompressao (Airlock)        */
/* ------------------------------------------------------------------ */
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
    if (F->tamanho >= MAX_AIRLOCK) {
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

/* ------------------------------------------------------------------ */
/*  Deque Dinamico — Central de Suprimentos                           */
/* ------------------------------------------------------------------ */
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

void inicializarDeque(DequeSuprimentos* D) {
    D->frente  = NULL;
    D->cauda   = NULL;
    D->tamanho = 0;
}

void inserirFrenteDeque(DequeSuprimentos* D, const char* item, int prio) {
    NoDeque* novo = (NoDeque*) malloc(sizeof(NoDeque));
    if (!novo) return;
    strncpy(novo->item, item, 79);
    novo->item[79] = '\0';
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
    }else{
        D->frente = novo;
    }     
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

/* ------------------------------------------------------------------ */
/*  main                                                               */
/* ------------------------------------------------------------------ */
int main(void) {

    ListaTripulacao  manifesto;
    PilhaMissoes     historico;
    FilaAirlock      airlock;
    DequeSuprimentos suprimentos;

    inicializarLista      (&manifesto);
    inicializarPilha      (&historico);
    inicializarFilaAirlock(&airlock);
    inicializarDeque      (&suprimentos);

    /* tripulantes de teste */
    Tripulante t1 = {1, "Cmdt. Ripley",   "Comandante", 98.5f};
    Tripulante t2 = {2, "Eng. Spock",     "Engenharia",  95.0f};
    Tripulante t3 = {3, "Dr. McCoy",      "Medicina",    99.1f};
    Tripulante t4 = {4, "Sgt. Vasquez",   "Seguranca",   97.3f};
    Tripulante t5 = {5, "Pilot. Han Solo","Navegacao",   96.0f};

    inserirTripulante(&manifesto, t1);
    inserirTripulante(&manifesto, t2);
    inserirTripulante(&manifesto, t3);
    imprimirManifesto(&manifesto);

    printf("\nMedia de oxigenio da tripulacao: %.2f%%\n",
       calcularMediaOxigenio(&manifesto));

    /* missoes */
    empilharMissao(&historico, "Reconhecimento LV-426",   72);
    empilharMissao(&historico, "Reparo Painel Solar B",    8);
    empilharMissao(&historico, "Coleta Amostras Titan",   24);

    char* ultima = desempilharMissao(&historico);
    printf("\nUltima missao registrada: %s\n", ultima);
    free(ultima);

    /* airlock — capacidade declarada: 4 */
    enfileirarAirlock(&airlock, t1);
    enfileirarAirlock(&airlock, t2);
    enfileirarAirlock(&airlock, t3);
    enfileirarAirlock(&airlock, t4);
    enfileirarAirlock(&airlock, t5);   /* quinto tripulante */

    /* suprimentos */
    inserirFrenteDeque(&suprimentos, "Oxigenio Liquido",  1);
    inserirFundoDeque (&suprimentos, "Racao Espacial",    3);
    inserirFundoDeque (&suprimentos, "Combustivel Xenon", 2);
    imprimirDeque(&suprimentos);

    return 0;
}
