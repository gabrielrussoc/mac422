#include <stdio.h>
#include <stdlib.h>
#include "atleta.h"
#include "utilitarios.h"

int sorteia_vel (int id) {
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
    if (cic[id].pos == cic[id].largada && !cic[id].meio) {
        cic[id].volta++;
/*        {
            int *ord, eq = 0, i;
            if (id / g_n == 0) {
                eq = 0;
                ord = ord_a;
            }
            else {
                eq = 1;
                ord = ord_b;
            }

            if (ord[2] == id) { 
                printf ("Terceiro colocado da equipe %c esta na volta: %d com tempo: %ds\n", 'A' + eq, cic[id].volta, tempo);
                for (i = 0; i < 3; i++) {
                    printf ("%d: ciclista %d \n", i + 1, ord_a[i]);
                }
            }
        } */
    }
}

void arruma_ordem (int id) {
    int *ord, pos = 0, i;
    if (id / g_n == 0) 
        ord = ord_a;
    else
        ord = ord_b;

    for (i = 0; i < g_n; i++)
        if (ord[i] == id) {
            pos = i;
            break;
        }

    for (i = pos; i < g_n - 1; i++)
        ord[i] = ord[i + 1];
    ord[g_n-1] = id;
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
    }
    else 
        ret = FALSE;
    pthread_mutex_unlock (&mutex_q);

    return ret;
}
