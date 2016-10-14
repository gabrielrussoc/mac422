#include <stdio.h>
#include <stdlib.h>
#include "atleta.h"
#include "utilitarios.h"

int sorteia_vel (int id) {
    double r;
    if (g_modo == 'u') return 1;

    /* Sorteia aleatoriamente entre 30km/h = 0 e 60km/h = 1 */
    r = (double) rand () / RAND_MAX;
    printf ("%f\n", r);
    if (cic[id].volta > 0 && r <= 0.5) 
        return 1;
    else 
        return 0; 
}

void atualiza_pos (int id) {
    cic[id].pos = (cic[id].pos + cic[id].vel) % g_d;
    if (cic[id].meio && cic[id].vel == 0) {
        cic[id].meio = FALSE;
        cic[id].pos = (cic[id].pos + 1) % g_d;
    }
    else if (!cic[id].meio && cic[id].vel == 0)
        cic[id].meio = TRUE;
}

void atualiza_volta (int id, int tempo) {
    int eq = 0;

    if (cic[id].pos == cic[id].largada && !cic[id].meio) {
        cic[id].volta++;
        cic[id].vel = sorteia_vel (id);
        printf ("Ciclista %d, com velocidade %d\n", id, cic[id].vel);
        eq = id / g_n;
        if (ord[eq][2] == id) {
            printf ("Terceiro colocado da equipe %c esta na volta: %d com tempo: %ds\n"
                    "1: ciclista %d\n"
                    "2: ciclista %d\n"
                    "3: ciclista %d\n",
                    'A' + eq, cic[id].volta, tempo, ord[eq][0], ord[eq][1], ord[eq][2]);
       } 
    }
}

void arruma_ordem (int id) {
    int pos = 0, i, eq;
    eq = id / g_n;

    for (i = 0; i < g_n; i++)
        if (ord[eq][i] == id) {
            pos = i;
            break;
        }

    for (i = pos + 1; i < g_n; i++) {
        ord[eq][i-1] = ord[eq][i];
    }
    ord[eq][g_n-1] = id;
}

int quebra (int id) {
    int ret;
    int v = cic[id].volta;
    time_t t;
    srand((unsigned) time(&t));

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

        printf ("Ciclista %d quebrou na volta %d\n", id, cic[id].volta);
    }
    else 
        ret = FALSE;
    pthread_mutex_unlock (&mutex_q);

    return ret;
}
