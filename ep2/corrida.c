#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "atleta.h"
#include "utilitarios.h"

/* */
void *ciclista (void *p) {
    int id = *((int *) p);
    int tempo = 0, aux;

    cic[id].vel = sorteia_vel (id);
    while (cic[id].volta < NVOLTAS && !g_acabou) {
        if (quebra (id)) break;
        aux = cic[id].pos;
        if (atualiza_pos (id)) {
            atualiza_pista (aux, id);
            atualiza_volta (id, tempo);
        }
        sincroniza (FALSE);
        tempo++;
    }
    sincroniza (TRUE);

    cic[id].final = tempo;
    printf ("%d terminou em %d\n",id,tempo);
    free (p);
    pthread_exit (NULL);
}

int main (int argc, char **argv) {
    int i, *j;
    pthread_t *pid;

    if (argc != 4 && argc != 5) {
        fprintf (stderr, "Uso: ./ep2 d n [v|u] [d]\n");
        return EXIT_FAILURE;
    }
    g_d = atoi (argv[1]);
    g_n = atoi (argv[2]);
    g_modo = argv[3][0];
    g_debug = 0;
    if (argc == 5  && argv[4][0] == 'd')
        g_debug = 1;

    init ();
    pid = malloc (2 * g_n * sizeof (pthread_t));

    /* Equipe A */
    for (i = 0; i < g_n; i++) {
        ord[0][i] = i;
        cic[i].id = i;
        cic[i].largada = 0;
        cic[i].volta = (i == 0 ? 0 : -1);
        cic[i].pos = (cic[i].largada - i + g_d) % g_d;
        cic[i].pos_eq = i;
        cic[i].quebrado = FALSE;
        cic[i].meio = FALSE;
        cic[i].proibe = TRUE;
        pista[cic[i].pos][0] = i;
        j = malloc (sizeof (int));
        *j = i;
        pthread_create (&pid[i], NULL, ciclista, j);
    }

    /* Equipe B */
    for (i = g_n; i < 2 * g_n; i++) {
        ord[1][i - g_n] = i;
        cic[i].id = i;
        cic[i].largada = g_d / 2;
        cic[i].volta = (i == g_n ? 0 : -1);
        cic[i].pos = (cic[i].largada - (i - g_n) + g_d) % g_d;
        cic[i].pos_eq = i - g_n;
        cic[i].quebrado = FALSE;
        cic[i].meio = FALSE;
        cic[i].proibe = TRUE;
        pista[cic[i].pos][0] = i;
        j = malloc (sizeof (int));
        *j = i;
        pthread_create (&pid[i], NULL, ciclista, j);
    }
    for (i = 0; i < g_n; i++) pthread_join (pid[i], NULL);
    checa_vitoria ();

    destroi ();
    
    return EXIT_SUCCESS;    
}

