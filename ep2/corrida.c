#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "atleta.h"
#include "utilitarios.h"

void *ciclista (void *p) {
    int id = *((int *) p);
    int tempo = 0, aux;
    while (cic[id].volta < NVOLTAS) {
        if (quebra (id)) break;
        cic[id].vel = sorteia_vel (id);
        aux = cic[id].pos;
        atualiza_pos (id);
        atualiza_pista (aux, cic[id].pos);
        atualiza_volta (id);
        sincroniza (id);
        tempo++;
    }
    cic[id].final = tempo;
    pthread_exit (NULL);
}

int main (int argc, char **argv) {
    int i;
    pthread_t pid[MAXN];
    if (argc != 4) {
        fprintf (stderr, "Uso: ./ep2 d n [v|u]\n");
        return EXIT_FAILURE;
    }
    g_d = atoi (argv[1]);
    g_n = atoi (argv[2]);
    g_modo = argv[3][0];

    init ();

    /* Equipe A */
    for (i = 0; i < g_n; i++) {
        ord_a[i] = i;
        cic[i].id = i;
        cic[i].largada = 0;
        cic[i].volta = i == 0 ? 0 : -1;
        cic[i].pos = (cic[i].largada - i + g_d) % g_d;
        cic[i].pos_eq = i;
        cic[i].prox = (i + 1) % (2 * g_n);
        cic[i].ant = (i - 1 + 2 * g_n) % (2 * g_n);
        cic[i].quebrado = FALSE;
        cic[i].meio = FALSE;
        pista[cic[i].pos][0] = i;
        pthread_create (&pid[i], NULL, ciclista, &i);
    }

    /* Equipe B */
    for (i = g_n; i < 2 * g_n; i++) {
        ord_b[i - g_n] = i;
        cic[i].id = i;
        cic[i].largada = g_d / 2;
        cic[i].volta = i == g_n ? 0 : -1;
        cic[i].pos = (cic[i].largada - (i - g_n) + g_d) % g_d;
        cic[i].pos_eq = i - g_n;
        cic[i].prox = (i + 1) % (2 * g_n);
        cic[i].ant = (i - 1 + 2 * g_n) % (2 * g_n);
        cic[i].quebrado = FALSE;
        cic[i].meio = FALSE;
        pista[cic[i].pos][0] = i;
        pthread_create (&pid[i], NULL, ciclista, &i);
    }

    for (i = 0; i < 2 * g_n; i++) pthread_join (pid[i], NULL);

    return EXIT_SUCCESS;    
}

