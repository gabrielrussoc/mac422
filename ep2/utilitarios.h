#ifndef _UTILITARIOS_H
#define _UTILITARIOS_H

#include <pthread.h>
#include "corrida.h"

#define NVOLTAS 16

#define TRUE 1
#define FALSE 0

#define A_VITORIA 1
#define B_VITORIA 2
#define EMPATE 3

/* Variaveis globais */
extern char g_modo;
extern int g_ultra3;
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
extern pthread_mutex_t mutex_ord[2];
extern pthread_mutex_t mutex_q;
extern pthread_mutex_t mutex_pista;
extern pthread_mutex_t mutex_sinc;

/* Variavel de condicao para a barreira de sincronizacao */
extern pthread_cond_t barreira;

/* Inicializa as variaveis e vetores globais e os mutexes */
void inicializa ();

/* Libera as variaveis e vetores globais e os mutexes */
void destroi ();

/* Imprime as informacoes necessarias para o modo de debug 
 * no instante iter */
void imprime_debug (int iter);

/* Verifica qual equipe venceu a corrida e imprime o resultado na saida
 * padrao */
void checa_vitoria ();

#endif
