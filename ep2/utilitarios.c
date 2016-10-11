#include "utilitarios.h"

char g_modo;
int g_n;
int g_d;
atleta cic[MAXN];
int pista[MAXD][2];
int ord_a[MAXN];
int ord_b[MAXN];
int quebrado[NVOLTAS];
int restante[2];
pthread_mutex_t mutex_c[MAXN];
pthread_mutex_t mutex_q;
pthread_mutex_t mutex_pista;

void init () {
    int i;
    pthread_mutex_init (&mutex_q, NULL);
    pthread_mutex_init (&mutex_pista, NULL);
    for (i = 0; i < 2*g_n; i++) 
        pthread_mutex_init (&mutex_c[i], NULL);
    for (i = 0; i < NVOLTAS; i++) 
        quebrado[i] = FALSE;
    restante[0] = restante[1] = g_n;
    for (i = 0; i < g_d; i++) 
        pista[i][0] = pista[i][1] = -1;
}

void P (pthread_mutex_t* mutex) {
    pthread_mutex_lock (mutex);
}

void V (pthread_mutex_t* mutex) {
    pthread_mutex_unlock (mutex);
}

void sincroniza (int id) {
    V (&mutex_c[id]);
    P (&mutex_c[cic[id].prox]);
}

void atualiza_pista (int ant, int id) {
    int prox = cic[id].pos;
    int faixa;

    P (&mutex_pista);
    faixa = (pista[ant][1] == id);
    pista[ant][faixa] = -1;
    faixa = (pista[prox][1] == -1);
    pista[prox][faixa] = id;
    V (&mutex_pista);
}

