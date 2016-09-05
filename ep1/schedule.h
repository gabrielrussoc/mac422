#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "process.h"

/* Resume a thread atrelada ao processo p */
void thread_wake (Process p);

/* Para a thread atrelada ao processo p */
void thread_sleep (Process p);

/* Funcao que cada thread executada, consumindo tempo de CPU. */
void *do_something (void *a);

/* Escalona os processos de in com o algoritmo FCFS */
void fcfs (FILE *in);

double elapsed ();

#endif

