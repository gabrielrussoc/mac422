#ifndef _ATLETA_H
#define _ATLETA_H

typedef struct {
    int id;
    int largada, volta, final;
    int pos, pos_eq;
    int vel, meio;
    int quebrado;
    int proibe;
} atleta;

/* Recebe o identificador de um ciclista e devolve a
 * sua velocidade, determindada pelo modo de execucao */
int sorteia_vel (int id);

/* Recebe o identificador de um ciclista e tenta atualizar sua
 * posicao. Devolve TRUE quando possivel e FALSE caso contrario. */
int atualiza_pos (int id);

/* Atualiza a volta do ciclista id, se necessario */
void atualiza_volta (int id, int tempo);

/* Funcao que faz a barreira de sincronizacao das threads e
 * verifica se ha um vencedor (se o terceiro ciclista de uma 
 * equipe ultrapassa o terceiro da outra equipe).
 * Recebe um interio que significa se a thread que alcancou a 
 * barreira sera destruida ou nao, para manter a sicronizacao */
void sincroniza (int saindo);

/* Recebe o id de um ciclista e a sua posicao na iteracao, atualiza
 * o vetor que representa a pista */
void atualiza_pista (int ant, int id);

/* Verifica que equipe venceu a corrida e imprime o resultado na saida
 * padrao */
void checa_vitoria ();

/* verifica se o terceiro ciclista de uma equipe ultrapassou
 * o terceiro da outra equipe. Se sim, determina a equipe
 * vencedora */ 
void checa_terceiro ();

/* Determina se o cilcista id ira "quebrar" devolve se ele 
 * quebrou ou nao */
int quebra (int id);

void remove_cic (int id);

#endif

