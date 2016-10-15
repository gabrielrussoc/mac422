#ifndef _UTILITARIOS_H
#define _UTILITARIOS_H

#include <pthread.h>
#include "atleta.h"

#define NVOLTAS 16

#define TRUE 1
#define FALSE 0

/* Variaveis globais */
extern char g_modo;
extern int g_debug;
extern int g_n;
extern int g_correndo;
extern int g_d;
extern int g_acabou;
extern int g_chegou;

/* Vetores globais */
extern atleta *cic;
extern int **pista;
extern int **ord;
extern int quebrado[NVOLTAS];
extern int restante[2];

/* Mutexes */
extern pthread_mutex_t mutex_q;
extern pthread_mutex_t mutex_pista;
extern pthread_mutex_t mutex_sinc;

/* Variavel de condicao para a barreira de sincronizacao */
extern pthread_cond_t barreira;

/* Inicializa as variaveis e vetores globais e os mutexes */
void init ();

/* Libera as variaveis e vetores globais e os mutexes */
void destroi ();

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

#endif
