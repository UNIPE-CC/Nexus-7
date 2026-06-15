/* ------------------------------------------------------------------ */
/*  main                                                               */
/* ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

#define MAX_AIRLOCK 4
#define MAX_STR     50

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

    /* missoes */
    empilharMissao(&historico, "Reconhecimento LV-426",   72);
    empilharMissao(&historico, "Reparo Painel Solar B",    8);
    empilharMissao(&historico, "Coleta Amostras Titan",   24);

    char* ultima = desempilharMissao(&historico);
    printf("\nUltima missao registrada: %s\n", ultima);

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