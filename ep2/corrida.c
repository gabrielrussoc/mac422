#include <stdio.h>
#include <stdlib.h>
#include "corrida.h"
#include "utilitarios.h"

/* Arruma a ordem da equipe do ciclista id (quando ele
 * quebra) */ 
static void arruma_ordem (int id);

/* Verifica se o terceiro ciclista de uma equipe ultrapassou
 * o terceiro da outra equipe. Se sim, determina a equipe
 * vencedora */ 
static void checa_terceiro ();


int sorteia_vel (int id) {
    int i, eq, ret, v;

    /* Velocidade uniforme */
    if (g_modo == 'u') return 1;

    /* Todos andam a 30km/h na primeira volta */
    if (cic[id].volta <= 0) return 0;

    eq = id / g_n;

    pthread_mutex_lock (&mutex_ord[eq]);
    /* Verifica se esta limitado por alguem em sua frente */
    v = cic[id].volta;
    for (i = cic[id].pos_eq - 1; i >= 0 && cic[ord[eq][i]].volta == v; i--)
        if (cic[ord[eq][i]].proibe) {
            cic[id].proibe = FALSE;
            pthread_mutex_unlock (&mutex_ord[eq]);
            return 0;
        }
    pthread_mutex_unlock (&mutex_ord[eq]);

    /* Sorteia aleatoriamente entre 30km/h e 60km/h */
    ret = (((double) rand () / RAND_MAX) < .5); 
    cic[id].proibe = !(ret | cic[id].proibe);
    return ret;
}

int atualiza_pos (int id) {
    int npos = (cic[id].pos + cic[id].vel) % g_d;
    int nmeio = cic[id].meio;
    int ret = TRUE, eq, faixa, oid, oeq;

    /* Calcula proxima posicao no caso de 30km/h */
    if (cic[id].meio && cic[id].vel == 0) {
        nmeio = FALSE;
        npos = (cic[id].pos + 1) % g_d;
    } else if (!cic[id].meio && cic[id].vel == 0)
        nmeio = TRUE;
    
    /* Verifica se ha espaco para o ciclista se mover */
    pthread_mutex_lock (&mutex_pista);
    if (pista[npos][0] != -1 && pista[npos][1] != -1)
        if (npos != cic[id].pos)
            ret = FALSE;
    pthread_mutex_unlock (&mutex_pista);
    if (!ret) return ret;

    /* Atualiza a posicao relativa na equipe */
    eq = id / g_n;

    pthread_mutex_lock (&mutex_pista);
    faixa = (pista[cic[id].pos][1] == id);
    oid = pista[cic[id].pos][!faixa];
    pthread_mutex_unlock (&mutex_pista);

    if (oid != -1 && npos != cic[id].pos) {
        oeq = oid / g_n;
        pthread_mutex_lock (&mutex_ord[eq]);
        if (oeq == eq && cic[id].pos_eq == cic[oid].pos_eq + 1 && 
                                        cic[id].volta == cic[oid].volta) {
            ord[eq][cic[id].pos_eq] = oid;
            cic[id].pos_eq--;
            ord[eq][cic[oid].pos_eq] = id;
            cic[oid].pos_eq++;
        } else if (oeq != eq) {
            checa_terceiro (id, oid);
        }
        pthread_mutex_unlock (&mutex_ord[eq]);
    }

    cic[id].pos = npos;
    cic[id].meio = nmeio;
    cic[id].acc += 1 + cic[id].vel;

    return ret;
}

void atualiza_volta (int id, int t) {
    int eq = 0;

    if (cic[id].pos == cic[id].largada && !cic[id].meio) {
        cic[id].volta++;
        cic[id].vel = sorteia_vel (id);
        eq = id / g_n;

        /* Imprime os tres primeiros no caso do terceiro colocado cruzar a linha */
        pthread_mutex_lock (&mutex_ord[eq]);
        if (ord[eq][2] == id) {
            printf ("Terceiro colocado da equipe %c esta na volta %d (%d u.t.)\n"
                    "1: ciclista %d\n"
                    "2: ciclista %d\n"
                    "3: ciclista %d\n",
                    'A' + eq, cic[id].volta, t, ord[eq][0], ord[eq][1], ord[eq][2]);
        } 
        pthread_mutex_unlock (&mutex_ord[eq]);
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

void sincroniza (int saindo) {
    static int iter = 1;

    pthread_mutex_lock (&mutex_sinc);
    if (g_correndo != 1) {
        if (saindo) g_correndo--;
        g_chegou = (g_chegou + !saindo) % g_correndo;
        if (g_chegou == 0) {
            if (g_debug && !g_acabou)
                imprime_debug (iter++);
            if (g_acabou) g_ultra3 = TRUE;
            pthread_cond_broadcast (&barreira);
        }
        else
            pthread_cond_wait (&barreira, &mutex_sinc);
    }
    pthread_mutex_unlock (&mutex_sinc);
}

int quebra (int id) {
    int ret;
    int v = cic[id].volta;

    pthread_mutex_lock (&mutex_q);
    if (v == 0) ret = FALSE;
    else if (v % 4 != 0) ret = FALSE;
    else if (quebrado[v]) ret = FALSE;
    else if (restante[id / g_n] < 4) ret = FALSE;
    else if ((double) rand () / RAND_MAX <= 0.1) {
        quebrado[v] = TRUE;
        restante[id / g_n]--;
        cic[id].quebrado = TRUE;
        arruma_ordem (id);
        ret = TRUE;

        printf ("QUEBROU: Ciclista %d na volta %d na posicao %d\n", id, cic[id].volta, cic[id].pos);
    }
    else 
        ret = FALSE;
    pthread_mutex_unlock (&mutex_q);

    return ret;
}

void remove_cic (int id) {
    int faixa;

    pthread_mutex_lock (&mutex_pista);
    faixa = (pista[cic[id].pos][1] == id);
    pista[cic[id].pos][faixa] = -1;
    pthread_mutex_unlock (&mutex_pista);
}



/*/// Funcoes Auxiliares ///////////////////////////////////////////////
 * ////////////////////////////////////////////////////////////////// */

static void checa_terceiro (int id, int oid) {
    if (cic[id].pos_eq == 2 && cic[oid].pos_eq == 2 && cic[id].acc > cic[oid].acc) {
        if (id / g_n == 0) g_acabou = A_VITORIA;
        else g_acabou = B_VITORIA;
    }
}


static void arruma_ordem (int id) {
    int i, eq;
    eq = id / g_n;
    pthread_mutex_lock (&mutex_ord[eq]);
    for (i = cic[id].pos_eq + 1; i < g_n; i++) {
        ord[eq][i-1] = ord[eq][i];
        cic[ord[eq][i-1]].pos_eq--;
    }
    ord[eq][g_n-1] = id;
    cic[id].pos_eq = g_n-1;
    pthread_mutex_unlock (&mutex_ord[eq]);
}

