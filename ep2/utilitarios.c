#include <stdio.h>
#include "utilitarios.h"

char g_modo;
int g_n;
int g_correndo;
int g_d;
int g_acabou;
int g_chegou;
atleta cic[MAXN];
int pista[MAXD][2];
int ord_a[MAXN];
int ord_b[MAXN];
int quebrado[NVOLTAS];
int restante[2];
pthread_mutex_t mutex_q;
pthread_mutex_t mutex_pista;
pthread_mutex_t mutex_sinc;
pthread_cond_t barreira;

void init () {
    int i;
    g_correndo = g_n * 2;
    pthread_mutex_init (&mutex_q, NULL);
    pthread_mutex_init (&mutex_pista, NULL);
    pthread_mutex_init (&mutex_sinc, NULL);
    pthread_cond_init (&barreira, NULL);
    g_chegou = 0;
    for (i = 0; i < NVOLTAS; i++) 
        quebrado[i] = FALSE;
    restante[0] = restante[1] = g_n;
    for (i = 0; i < g_d; i++) 
        pista[i][0] = pista[i][1] = -1;
}

void checa_terceiro () {
    int a3 = ord_a[2], b3 = ord_b[2], va, vb;
    if (cic[a3].pos == cic[b3].pos) {
        va = cic[a3].vel;
        vb = cic[b3].vel;
        if (va > vb) g_acabou = 1; /* A ganhou */
        else if (va < vb) g_acabou = 2; /* B ganhou */
    }
}

void checa_vitoria () {
    int i, a, b;
    if (!g_acabou) {
        a = cic[ord_a[2]].final;
        b = cic[ord_b[2]].final;
        if (a < b) g_acabou = 1; /* A ganhou */
        else if (b < a) g_acabou = 2; /* B ganhou */
        else g_acabou = 3;
    }
    switch (g_acabou) {
        case 1:
            puts ("A ganhou!");
            break; 
        case 2:
            puts ("B ganhou!");
            break;
        case 3:
            puts ("Empate!");
            break;
    }
    printf ("Equipe A %14c Equipe B\n", ' ');
    for (i = 0; i < g_n; i++) {
        printf ("%d: ciclista %d (%ds)%s%4c", i + 1, ord_a[i], cic[ord_a[i]].final, cic[ord_a[i]].quebrado ? "*" : "", ' ');
        printf ("%d: ciclista %d (%ds)%s\n", i + 1, ord_b[i], cic[ord_b[i]].final, cic[ord_b[i]].quebrado ? "*" : "");
    }
    printf ("\n*: Ciclistas que quebraram\n");

}

void sincroniza (int saindo) {
    pthread_mutex_lock (&mutex_sinc);
    if (g_correndo != 1) {
        if (saindo) g_correndo--;
        g_chegou = (g_chegou + !saindo) % g_correndo;
        if (g_chegou == 0) {
            checa_terceiro ();
            pthread_cond_broadcast (&barreira);
        }
        else
            pthread_cond_wait (&barreira, &mutex_sinc);
        pthread_mutex_unlock (&mutex_sinc);
    }
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

