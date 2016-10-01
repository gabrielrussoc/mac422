#include <stdio.h>

void *thread_ciclista (void *p) {
    int id = *((int *) p);
    int tempo = 0, aux;
    while (ciclista[id].volta < NVOLTAS) {
        if (quebra (id, volta)) break;
        ciclista[id].vel = sorteia_vel (id);
        aux = ciclista[id].pos;
        atualiza_pos (id);
        atualiza_pista (aux, ciclista[id].pos);
        atualiza_volta;
        sincroniza (id);
        tempo++;
    }
    ciclista[id].final = tempo;
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

    for (i = 0; i < g_d; i++) 
        pista[i][0] = pista[i][1] = -1;

    /* Equipe A */
    for (i = 0; i < n; i++) {
        ord_a[i] = i;
        ciclista[i].id = i;
        ciclista[i].largada = 0;
        ciclista[i].volta = i == 1 ? 0 : -1;
        ciclista[i].pos = (largada - i + g_d) % g_d;
        ciclista[i].pos_eq = i;
        ciclista[i].quebrado = FALSE;
        ciclista[i].meio = FALSE;
        pista[ciclista[i].pos][0] = i;
        pthread_create (&pid[i], NULL, thread_ciclista, &i);
    }

    /* Equipe B */
    for (i = n; i < 2 * n; i++) {
        ord_b[i - n] = i;
        ciclista[i].id = i;
        ciclista[i].largada = d / 2;
        ciclista[i].volta = i == 1 ? 0 : -1;
        ciclista[i].pos = (largada - (i - n) + g_d) % g_d;
        ciclista[i].pos_eq = i - n;
        ciclista[i].quebrado = FALSE;
        ciclista[i].meio = FALSE;
        pista[ciclista[i].pos][0] = i;
        pthread_create (&pid[i], NULL, thread_ciclista, &i);
    }

    for (i = 0; i < 2 * n; i++) pthread_join (pid[i], NULL);

    return EXIT_SUCCESS;    
}

