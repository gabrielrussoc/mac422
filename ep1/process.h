#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdio.h>
#include <pthread.h>

/* Biblioteca dos processos 
 * Guarda suas informações e funções relacionadas a eles
 * */

typedef char* string;

typedef struct {
    double t0;
    string name;
    double dt;
    double deadline;
    int paused;
    pthread_cond_t cond;
    double running;
    int level;
} process;

typedef process* Process;

/* Cria um novo processo */
Process process_create (double t0, string name, double dt, double deadline);

/* Destroi o processo p */
void process_destroy (Process p);

/* Le um processo do arquivo in */
Process process_read (FILE *in);

/* Devolve o tempo restante de um processo */
double process_remaining (Process p);

/* Devolve quantos quanta o processo p tem disponivel,
 * com base em sua classe (para o escalonamento com multiplas
 * filas). */
double process_quantum (Process p);

#endif

