#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "atleta.h"
#include "utilitarios.h"

void *ciclista (void *p) {
    int id = *((int *) p);
    int tempo = 0, aux;
    while (cic[id].volta < NVOLTAS && !g_acabou) {
        if (quebra (id)) break;
        cic[id].vel = sorteia_vel (id);
        aux = cic[id].pos;
        atualiza_pos (id);
        atualiza_pista (aux, cic[id].pos);
        atualiza_volta (id, tempo);
        sincroniza (FALSE);
        tempo++;
    }
    sincroniza (TRUE);

    cic[id].final = tempo;
    free (p);
    pthread_exit (NULL);
}

int main (int argc, char **argv) {
    int i, *j;
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
        cic[i].volta = (i == 0 ? 0 : -1);
        cic[i].pos = (cic[i].largada - i + g_d) % g_d;
        cic[i].quebrado = FALSE;
        cic[i].meio = FALSE;
        pista[cic[i].pos][0] = i;
        j = malloc (sizeof (int));
        *j = i;
        pthread_create (&pid[i], NULL, ciclista, j);
    }

    /* Equipe B */
    for (i = g_n; i < 2 * g_n; i++) {
        ord_b[i - g_n] = i;
        cic[i].id = i;
        cic[i].largada = g_d / 2;
        cic[i].volta = (i == g_n ? 0 : -1);
        cic[i].pos = (cic[i].largada - (i - g_n) + g_d) % g_d;
        cic[i].quebrado = FALSE;
        cic[i].meio = FALSE;
        pista[cic[i].pos][0] = i;
        j = malloc (sizeof (int));
        *j = i;
        pthread_create (&pid[i], NULL, ciclista, j);
    }
    for (i = 0; i < g_n; i++) pthread_join (pid[i], NULL);
    checa_vitoria ();
    
    return EXIT_SUCCESS;    
}

