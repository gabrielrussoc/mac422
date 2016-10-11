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

void atualiza_volta (int id) {
    if (cic[id].pos == cic[id].largada && !cic[id].meio)
        cic[id].volta++;
}

int quebra (int id) {
    int ret;
    int v = cic[id].volta;
    P (&mutex_q);
    if (v == 0) ret = FALSE;
    else if (v % 4 != 0) ret = FALSE;
    else if (quebrado[v]) ret = FALSE;
    else if (restante[id / g_n] < 4) ret = FALSE;
    else if ((double) rand () / RAND_MAX <= 0.1) {
        quebrado[v] = TRUE;
        restante[id / g_n]--;
        cic[id].quebrado = TRUE;

        /* Atualiza a sincronizacao */
        cic[cic[id].ant].prox = cic[id].prox;
        cic[cic[id].prox].ant = cic[id].ant;

        ret = TRUE;
    }
    else 
        ret = FALSE;
    V (&mutex_q);

    return ret;
}
