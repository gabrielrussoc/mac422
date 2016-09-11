#ifndef _UTILITY_H
#define _UTILITY_H

#include <stdio.h>
#include "process.h"
#include "heap.h"
#include "queue.h"

/* Biblioteca de utilidade
 * Guarda variaveis globais, constantes, funcoes de uso
 * geral e etc */

/* Constantes */
#define TRUE 1
#define FALSE 0
#define MAX 1024
#define EPS 1e-3
#define NQUEUES 8

/* Variáveis globais */

/* Arquivos de entrada e Saida */
extern FILE *g_in, *g_out;

/* Mutexes */
extern pthread_mutex_t g_tlock;    
extern pthread_mutex_t g_slock;

/* Estruturas */
extern Queue g_queue;
extern Heap g_heap;
extern Queue *g_multi_queues;

/* Variaveis Auxiliares */
extern int g_cpu;
extern int g_thread;
extern int g_debug;
extern int g_context;
extern Process g_cpu_process;
extern int g_scheduler;
extern double g_start;

/* Resume a thread atrelada ao processo p */
void thread_wake (Process p);

/* Para a thread atrelada ao processo p */
void thread_sleep (Process p);

/* Trava a thread do processo p caso esta esteja pausada ou nao faz nada.
 * Devolve o tempo que a thread ficou travada. */
double thread_check (Process p);

/* Inicializa os mutex que serao utilizados */
void mutex_init ();

/* Libera os mutex que foram utilizados */
void mutex_destroy ();

/* Devolve a quantidade de segundos desde o inicio do programa */
double elapsed ();

#endif
