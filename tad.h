/* ------------------------------------------------------------------ */
/*  TAD Tripulante                                                      */
/* ------------------------------------------------------------------ */
#ifndef TAD_H
#define TAD_H

#define MAX_AIRLOCK 4
#define MAX_STR 50

typedef struct {
    int   id;
    char  nome[MAX_STR];
    char  especialidade[MAX_STR];
    float nivel_oxigenio;   /* percentual: 0.0 a 100.0 */
} Tripulante;

/* Lista */
typedef struct NoLista {
    Tripulante dados;
    struct NoLista* prox;
} NoLista;

typedef struct {
    NoLista* cabeca;
    int tamanho;
} ListaTripulacao;

void inicializarLista(ListaTripulacao* L);
void inserirTripulante(ListaTripulacao* L, Tripulante t);
int removerTripulante(ListaTripulacao* L, int id);
void imprimirManifesto(ListaTripulacao* L);
float calcularMediaOxigenio(ListaTripulacao* L);


/* PILHA */

typedef struct NoPilha {
    char descricao[100];
    int duracao_h;
    struct NoPilha* prox;
} NoPilha;

typedef struct {
    NoPilha* topo;
    int tamanho;
} PilhaMissoes;

void inicializarPilha(PilhaMissoes* P);
void empilharMissao(PilhaMissoes* P, const char* desc, int horas);
char* desempilharMissao(PilhaMissoes* P);

/* FILA */

typedef struct {
    Tripulante dados[MAX_AIRLOCK];
    int inicio;
    int fim;
    int tamanho;
} FilaAirlock;

void inicializarFilaAirlock(FilaAirlock* F);
int enfileirarAirlock(FilaAirlock* F, Tripulante t);
int desenfileirarAirlock(FilaAirlock* F, Tripulante* t);

/* DEQUE */

typedef struct NoDeque {
    char item[80];
    int prioridade;
    struct NoDeque* prox;
    struct NoDeque* ant;
} NoDeque;

typedef struct {
    NoDeque* frente;
    NoDeque* cauda;
    int tamanho;
} DequeSuprimentos;

void inicializarDeque(DequeSuprimentos* D);
void inserirFrenteDeque(DequeSuprimentos* D, const char* item, int prio);
void inserirFundoDeque(DequeSuprimentos* D, const char* item, int prio);
void imprimirDeque(DequeSuprimentos* D);

#endif