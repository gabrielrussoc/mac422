#ifndef _SCHEDULE_H
#define _SCHEDULE_H

/* Funcao que cada thread executada, consumindo tempo de CPU. */
void *do_something (void *a);

/* Funcao que cada thread executada, consumindo tempo de CPU. 
 * Usada no escalonamento de multiplas filas. */
void *do_something_else (void *a);

/* Escalona os processos com o algoritmo FCFS */
void fcfs ();

/* Escalona os processos com o algoritmo SRTN */
void srtn ();

#endif

