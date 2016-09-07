#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "process.h"


/* Funcao que cada thread executada, consumindo tempo de CPU. */
void *do_something (void *a);

/* Escalona os processos de in com o algoritmo FCFS */
void fcfs (FILE *in);

#endif

