#ifndef _UTILITARIOS_H
#define _UTILITARIOS_H

#include <pthread.h>
#include "atleta.h"

#define MAXN 1024
#define MAXD 65536
#define NVOLTAS 16

#define TRUE 1
#define FALSE 0

extern char g_modo;
extern int g_n;
extern int g_d;
extern atleta cic[MAXN];
extern int pista[MAXD][2];
extern int ord_a[MAXN];
extern int ord_b[MAXN];
extern int quebrado[NVOLTAS];
extern int restante[2];
extern pthread_mutex_t mutex_c[MAXN];
extern pthread_mutex_t mutex_q;
extern pthread_mutex_t mutex_pista;

void init ();
void P (pthread_mutex_t *mutex);
void V (pthread_mutex_t *mutex);
void sincroniza (int id);
void atualiza_pista (int ant, int id);

#endif
