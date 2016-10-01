#include "atleta.h"
#include <stdlib.h>

int sorteia_vel (int id) {
    return 1;
}

int atualiza_pos (int id) {
    ciclista[id].pos = (ciclista[id].pos + ciclista[id].vel) % g_d;
    if (ciclista[id].meio && ciclista[id].vel == 0) {
        ciclista[id].meio = 0;
        ciclista[id].pos = (ciclista[id].pos + 1) % g_d;
    }
}

int atualiza_volta (int id) {
    if (ciclista[id].pos == ciclista[id].largada && !ciclista[id].meio)
        ciclista[id].volta++;
}

int quebra (int id, int v) {
    double p;
    if (v == 0) return FALSE;
    if (v % 4 != 0) return FALSE;
    if (quebrado[v]) return FALSE;
    if (restante[id >= n] < 4) return FALSE;
    p = (double) rand () / RAND_MAX;
    if (p <= 0.1) {
        quebrado[v] = 1;
        restante[id >= n]--;
        return TRUE;
    }
    return FALSE;
}
    
