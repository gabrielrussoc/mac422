#ifndef _ATLETA_H
#define _ATLETA_H

typedef struct {
    int id;
    int largada, volta, final;
    int pos;
    int vel, meio;
    int quebrado;
} atleta;

/* Recebe o identificador de um ciclista e devolve a
 * sua velocidade, determindada pelo modo de execucao */
int sorteia_vel (int id);

/* Recebe o identificador de um ciclista e atualiza a 
 * sua posicao */
void atualiza_pos (int id);

/* Atualiza a volta do ciclista id, se necessario */
void atualiza_volta (int id, int tempo);

/* Determina se o cilcista id ira "quebrar" devolve se ele 
 * quebrou ou nao */
int quebra (int id);

#endif

