/* ------------------------------------------------------------------ */
/*  TAD Tripulante                                                      */
/* ------------------------------------------------------------------ */
typedef struct {
    int   id;
    char  nome[MAX_STR];
    char  especialidade[MAX_STR];
    float nivel_oxigenio;   /* percentual: 0.0 a 100.0 */
} Tripulante;