#ifndef _UTILITARIOS_H
#define _UTILITARIOS_H

#include <pthread.h>
#include "atleta.h"

#define MAXN 1024
#define MAXD 65536
#define NVOLTAS 16

#define TRUE 1
#define FALSE 0

#define A_VITORIA 1
#define B_VITORIA 2
#define EMPATE 3

extern char g_modo;
extern int g_n;
extern int g_correndo;
extern int g_d;
extern int g_acabou;
extern int g_chegou;
extern atleta cic[MAXN];
extern int pista[MAXD][2];
extern int ord_a[MAXN];
extern int ord_b[MAXN];
extern int quebrado[NVOLTAS];
extern int restante[2];
extern pthread_mutex_t mutex_q;
extern pthread_mutex_t mutex_pista;
extern pthread_mutex_t mutex_sinc;

extern pthread_cond_t barreira;

void init ();
void sincroniza (int saindo);
void atualiza_pista (int ant, int id);
void checa_vitoria ();
void checa_terceiro ();


#endif
