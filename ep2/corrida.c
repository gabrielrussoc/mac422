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
        atualiza_volta (id);
        sincroniza (id);
        tempo++;
    }
    cic[id].final = tempo;
    free (p);
    pthread_exit (NULL);
}

void *coordenador (void *p) {
    int i, a3, b3, f;
    while (TRUE) {
        for (i = 0; i < 2 * g_n; i++) {
            while (chegou[i] == FALSE);
            chegou[i] = FALSE;
        }

        /* terceiro colocado */
        a3 = ord_a[2];
        b3 = ord_b[2];
        if (cic[a3].pos == cic[b3].pos) {
            if (cic[a3].vel > cic[b3].vel) {
                g_acabou = 1; /* A ganhou */
                break;
            }
            else if (cic[a3].vel < cic[b3].vel) {
                g_acabou = 2; /* B ganhou */
                break;
            }
        }

        f = FALSE;
        for (i = 0; i < 2 * g_n; i++)
            f |= (cic[i].volta < NVOLTAS);
        
        if (!f) {
            g_acabou = 3; /* Empate */
            for (i = 0; i < g_n; i++) {
                if (cic[ord_a[i]].final < cic[ord_b[i]].final) {
                    g_acabou = 1; /* A ganhou */
                    break;
                } else if (cic[ord_a[i]].final > cic[ord_b[i]].final) {
                    g_acabou = 2; /* B ganhou */
                    break;
                }
            }
            break;
        }
            
        for (i = 0; i < 2 * g_n; i++)
            continua[i] = TRUE;
    }
    if (g_acabou == 1) {
        puts ("A ganhou");
    } else if (g_acabou == 2) {
        puts ("B ganhou");
    }
    else puts("empate");
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

    /* Coordenador */
    pthread_create(&pid[2 * g_n], NULL, coordenador, NULL);

    /* Equipe A */
    for (i = 0; i < g_n; i++) {
        ord_a[i] = i;
        cic[i].id = i;
        cic[i].largada = 0;
        cic[i].volta = (i == 0 ? 0 : -1);
        cic[i].pos = (cic[i].largada - i + g_d) % g_d;
        cic[i].pos_eq = i;
        cic[i].prox = (i + 1) % (2 * g_n);
        cic[i].ant = (i - 1 + 2 * g_n) % (2 * g_n);
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
        cic[i].pos_eq = i - g_n;
        cic[i].prox = (i + 1) % (2 * g_n);
        cic[i].ant = (i - 1 + 2 * g_n) % (2 * g_n);
        cic[i].quebrado = FALSE;
        cic[i].meio = FALSE;
        pista[cic[i].pos][0] = i;
        j = malloc (sizeof (int));
        *j = i;
        pthread_create (&pid[i], NULL, ciclista, j);
    }

    for (i = 0; i <= 2 * g_n; i++) pthread_join (pid[i], NULL);

    return EXIT_SUCCESS;    
}

