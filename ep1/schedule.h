#ifndef _SCHEDULE_H
#define _SCHEDULE_H

/* Biblioteca dos escalonadores 
 * Contem os algoritmos de escalonamento, assim como 
 * as funcoes que serao utilizadas nas threads */

/* Funcao que cada thread executada, consumindo tempo de CPU. */
void *do_something (void *a);

/* Funcao que cada thread executada, consumindo tempo de CPU. 
 * Usada no escalonamento de multiplas filas. */
void *do_something_else (void *a);

/* Escalona os processos com o algoritmo FCFS */
void fcfs ();

/* Escalona os processos com o algoritmo SRTN */
void srtn ();

/* Escalona os processos com o algoritmo de multiplas filas */
void multilevel ();

#endif

