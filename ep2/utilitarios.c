#include "utilitarios.h"

char g_modo;
int g_n;
int g_d;
int g_acabou;
atleta cic[MAXN];
int pista[MAXD][2];
int ord_a[MAXN];
int ord_b[MAXN];
int quebrado[NVOLTAS];
int restante[2];
int continua[MAXN];
int chegou[MAXN];
pthread_mutex_t mutex_q;
pthread_mutex_t mutex_pista;

void init () {
    int i;
    pthread_mutex_init (&mutex_q, NULL);
    pthread_mutex_init (&mutex_pista, NULL);
    for (i = 0; i < NVOLTAS; i++) 
        quebrado[i] = FALSE;
    restante[0] = restante[1] = g_n;
    for (i = 0; i < 2 * g_n; i++)
        chegou[i] = continua[i] = FALSE;
    for (i = 0; i < g_d; i++) 
        pista[i][0] = pista[i][1] = -1;
}

void sincroniza (int id) {
    chegou[id] = TRUE;
    while (continua[id] == FALSE);
    continua[id] = FALSE;
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

