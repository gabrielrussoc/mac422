#ifndef _ATLETA_H
#define _ATLETA_H

typedef struct {
    int id;
    int largada, volta, final;
    int pos, pos_eq;
    int vel, meio;
    int prox, ant;
    int quebrado;
} atleta;

/* Sorteia a velocidade do ciclista id */
int sorteia_vel (int id);
void atualiza_pos (int id);
void atualiza_volta (int id);
int quebra (int id);

#endif

