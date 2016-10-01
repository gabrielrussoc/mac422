#ifndef _ATLETA_H
#define _ATLETA_H

typedef struct {
    int id;
    int largada, volta, final;
    int pos, pos_eq;
    int vel, meio;
    int quebrado;
} atleta;

/* Sorteia a velocidade do ciclista id */
int sorteia_vel (int id);

#endif

