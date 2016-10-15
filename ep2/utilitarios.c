#include <stdio.h>
#include <stdlib.h>
#include "utilitarios.h"

char g_modo;
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
pthread_mutex_t mutex_q;
pthread_mutex_t mutex_pista;
pthread_mutex_t mutex_sinc;
pthread_cond_t barreira;

/* verifica se o terceiro ciclista de uma equipe ultrapassou
 * o terceiro da outra equipe. Se sim, determina a equipe
 * vencedora */ 
void checa_terceiro ();

/* Imprime as informacoes necessarias para o modo de debug */
void imprime_debug ();

void init () {
    int i;
    /* Inicando as variaves globais */
    g_correndo = g_n * 2;
    g_chegou = 0;

    /* Inicando os mutexes */
    pthread_mutex_init (&mutex_q, NULL);
    pthread_mutex_init (&mutex_pista, NULL);
    pthread_mutex_init (&mutex_sinc, NULL);
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


void sincroniza (int saindo) {
    pthread_mutex_lock (&mutex_sinc);
    if (g_correndo != 1) {
        if (saindo) g_correndo--;
        g_chegou = (g_chegou + !saindo) % g_correndo;
        if (g_chegou == 0) {
            checa_terceiro ();
            if (g_debug)
                imprime_debug ();
            pthread_cond_broadcast (&barreira);
        }
        else
            pthread_cond_wait (&barreira, &mutex_sinc);
    }
    pthread_mutex_unlock (&mutex_sinc);
}

void atualiza_pista (int ant, int id) {
    int prox = cic[id].pos;
    int faixa;

    pthread_mutex_lock (&mutex_pista);
    faixa = (pista[ant][1] == id);
    pista[ant][faixa] = -1;
    faixa = (pista[prox][1] == -1);
    pista[prox][faixa] = id;
    pthread_mutex_unlock (&mutex_pista);
}

void checa_vitoria () {
    int i, a, b;
    if (!g_acabou) {
        a = cic[ord[0][2]].final;
        b = cic[ord[1][2]].final;
        if (a < b) g_acabou = 1; /* A ganhou */
        else if (b < a) g_acabou = 2; /* B ganhou */
        else g_acabou = 3;
    }
    
    puts ("\nCorrida finalizada. Resultado:\n");
    switch (g_acabou) {
        case 1:
            printf ("%10cA ganhou!\n", ' ');
            break; 
        case 2:
            printf ("%10cB ganhou!\n", ' ');
            break;
        case 3:
            printf ("%10cEmpate!\n", ' ');
            break;
    }
    printf ("\nEquipe A\n");
    for (i = 0; i < g_n; i++) {
        printf ("%d: ciclista %d (%ds)", i + 1, ord[0][i], cic[ord[0][i]].final);
        if (cic[ord[0][i]].quebrado) 
            printf ("* (%d volta)", cic[ord[0][i]].volta);
        printf ("\n");
    } 
    printf ("\nEquipe B\n");
    for (i = 0; i < g_n; i++) {
        printf ("%d: ciclista %d (%ds)", i + 1, ord[1][i], cic[ord[1][i]].final);
        if (cic[ord[1][i]].quebrado) 
            printf ("* (%d volta)", cic[ord[1][i]].volta);
        printf ("\n");
    } 

    printf ("\n* (i): Ciclista quebrou na i-esima volta\n");

}

/*/// Funcoes Auxiliares ///////////////////////////////////////////////
 * ////////////////////////////////////////////////////////////////// */

void checa_terceiro () {
    int a3 = ord[0][2], b3 = ord[1][2], va, vb;
    if (cic[a3].pos == cic[b3].pos) {
        va = cic[a3].vel;
        vb = cic[b3].vel;
        if (va > vb) g_acabou = 1; /* A ganhou */
        else if (va < vb) g_acabou = 2; /* B ganhou */
    }
}

void imprime_debug () {
    int i;
    fprintf (stderr, "Estado da pista:\n");
    for (i = 0; i < g_d; i++)
        fprintf (stderr, "%d: %d %d    ", i, pista[i][0], pista[i][1]);
    fprintf (stderr, "\n\n");
}



