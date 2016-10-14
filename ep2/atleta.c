#include <stdio.h>
#include <stdlib.h>
#include "atleta.h"
#include "utilitarios.h"

int sorteia_vel (int id) {
    time_t t;
    if (g_modo == 'u') return 1;

    /* Sorteia aleatoriamente entre 30km/h = 0 e 60km/h = 1 */
    srand((unsigned) time(&t));
    if (cic[id].volta > 0 && (double) rand () / RAND_MAX <= 0.5) 
        return 1;
    else 
        return 0; 
    return 1;
}

void atualiza_pos (int id) {
    cic[id].pos = (cic[id].pos + cic[id].vel) % g_d;
    if (cic[id].meio && cic[id].vel == 0) {
        cic[id].meio = 0;
        cic[id].pos = (cic[id].pos + 1) % g_d;
    }
}

void atualiza_volta (int id, int tempo) {
    int eq = 0;

    if (cic[id].pos == cic[id].largada && !cic[id].meio) {
        cic[id].volta++;
        cic[id].vel = sorteia_vel (id);
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
