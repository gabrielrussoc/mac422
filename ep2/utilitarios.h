#ifndef _UTILITARIOS_H
#define _UTILITARIOS_H

#include <pthread.h>
#include "atleta.h"

#define NVOLTAS 16

#define TRUE 1
#define FALSE 0

#define A_VITORIA 1
#define B_VITORIA 2
#define EMPATE 3

/* Variaveis globais */
extern int g_end;
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
extern pthread_mutex_t mutex_ord[2];
extern pthread_mutex_t mutex_q;
extern pthread_mutex_t mutex_pista;
extern pthread_mutex_t mutex_sinc;

/* Variavel de condicao para a barreira de sincronizacao */
extern pthread_cond_t barreira;

/* Devolve o maximo entre a e b */
int max (int a, int b);

/* Troca o conteudo dos ponteiros a e b */
void swap (int *a, int *b);

/* Inicializa as variaveis e vetores globais e os mutexes */
void init ();

/* Libera as variaveis e vetores globais e os mutexes */
void destroi ();

/* Imprime as informacoes necessarias para o modo de debug */
void imprime_debug ();

#endif

