#ifndef _CORRIDA_H
#define _CORRIDA_H

typedef struct {
    int largada, volta, final;
    int pos, pos_eq;
    int vel, meio;
    int quebrado;
    int proibe;
    int acc;
} atleta;

/* Recebe o identificador de um ciclista e devolve a
 * sua velocidade, determindada pelo modo de execucao 
 * Devolve 0 para 30 km/h e 1 para 60 km/h */
int sorteia_vel (int id);

/* Recebe o identificador de um ciclista e tenta atualizar sua
 * posicao. Devolve TRUE quando possivel e FALSE caso contrario. 
 * Tambem determina se houve ultrapassengem entre os terceiros 
 * colocados */
int atualiza_pos (int id);

/* Atualiza a volta do ciclista id, se necessario. Se id representar
 * o terceiro ciclista de uma equipe e sua volta for atualizada, imprime
 * na saida padrao os tres primeiros da equipe no instante t */
void atualiza_volta (int id, int t);

/* Recebe o id de um ciclista e a sua posicao anterior. Atualiza
 * o vetor que representa a pista para a sua posicao atual */
void atualiza_pista (int ant, int id);

/* Funcao que faz a barreira de sincronizacao das threads.
 * Recebe um inteiroo que significa se a thread que alcancou a 
 * barreira sera destruida ou nao */
void sincroniza (int saindo);

/* Determina se o cilcista id ira "quebrar", devolve se ele 
 * quebrou */
int quebra (int id);

/* Remove o ciclista id da pista */
void remove_cic (int id);

#endif

