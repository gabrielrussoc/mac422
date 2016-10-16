#include <stdio.h>
#include <stdlib.h>
#include "utilitarios.h"

char g_modo;
int g_ultra3;
int g_debug;
int g_n;
int g_correndo;
int g_d;
int g_acabou;
int g_chegou;
atleta *cic;
int **pista;
int **ord;
int quebrado[NVOLTAS];
int restante[2];
pthread_mutex_t mutex_ord[2];
pthread_mutex_t mutex_q;
pthread_mutex_t mutex_pista;
pthread_mutex_t mutex_sinc;
pthread_cond_t barreira;

void inicializa () {
    int i;
    
    /* Inicializa a semente do rand com o tempo atual */
    srand (time (NULL));
    
    /* Inicando as variaves globais */
    g_correndo = g_n * 2;
    g_chegou = 0;
    g_acabou = 0;
    g_ultra3 = FALSE;
    
    /* Inicando os mutexes */
    pthread_mutex_init (&mutex_q, NULL);
    pthread_mutex_init (&mutex_pista, NULL);
    pthread_mutex_init (&mutex_sinc, NULL);
    pthread_mutex_init (&mutex_ord[0], NULL);
    pthread_mutex_init (&mutex_ord[1], NULL);
    pthread_cond_init (&barreira, NULL);

    /* Inicando as vetores globais */
    cic = malloc (2 * g_n * sizeof (atleta));

    pista = malloc (g_d * sizeof (int *));
    for (i = 0; i < g_d; i++) {
        pista[i] = malloc (2 * sizeof (int));
        pista[i][0] = pista[i][1] = -1;
    }

    ord = malloc (2 * sizeof (int *));
    ord[0] = malloc (g_n * sizeof (int));
    ord[1] = malloc (g_n * sizeof (int));

    for (i = 0; i < NVOLTAS; i++) 
        quebrado[i] = FALSE;
    restante[0] = restante[1] = g_n;
}

void destroi () {
    int i;

    /* Liberando os mutexes */
    pthread_mutex_destroy (&mutex_q);
    pthread_mutex_destroy (&mutex_pista);
    pthread_mutex_destroy (&mutex_sinc);
    pthread_mutex_destroy (&mutex_ord[0]);
    pthread_mutex_destroy (&mutex_ord[1]);
    pthread_cond_destroy (&barreira);

    /* Liberando as vetores globais */
    free (cic);

    for (i = 0; i < g_d; i++) 
        free (pista[i]);
    free (pista);

    free (ord[0]);
    free (ord[1]);
    free (ord);
}

void imprime_debug (int iter) {
    int i;
    fprintf (stderr, "Estado da pista no instante %d:\n", iter);
    for (i = 0; i < g_d; i++) {
        fprintf (stderr, "%d:", i);
        if (pista[i][0] != -1) fprintf (stderr, " %d", pista[i][0]);
        if (pista[i][1] != -1) fprintf (stderr, " %d", pista[i][1]);
        fprintf (stderr, "\n");
    }
    fprintf (stderr, "\n");
}

