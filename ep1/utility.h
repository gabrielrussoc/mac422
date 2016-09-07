#ifndef _UTILITY_H
#define _UTILITY_H

#include <stdio.h>
#include "process.h"
#include "heap.h"
#include "queue.h"

/* Constantes */
#define TRUE 1
#define FALSE 0
#define MAX 1024
#define EPS 1e-3

/* Variáveis globais */
extern FILE *g_in, *g_out;
extern pthread_mutex_t g_tlock;    
extern pthread_mutex_t g_slock;
extern pthread_mutex_t g_dlock;
extern Queue g_queue;
extern Heap g_heap;
extern int g_cpu;
extern int g_thread;
extern int g_debug;
extern int g_context;
extern int g_line;
extern Process g_cpu_process;

/* Resume a thread atrelada ao processo p */
void thread_wake (Process p);

/* Para a thread atrelada ao processo p */
void thread_sleep (Process p);

/* Trava a thread do processo p caso esta esteja pausada ou nao faz nada.
 * Devolve o tempo que a thread ficou travada. */
double thread_check (Process p);

/* Devolve a quantidade de segundos desde o inicio do programa */
double elapsed ();

#endif
