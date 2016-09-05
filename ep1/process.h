#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdio.h>
#include <pthread.h>

/* Biblioteca dos processos */

typedef char* string;

typedef struct {
    double t0;
    string name;
    double dt;
    double deadline;
    int paused;
    pthread_cond_t cond;
    double running;
} process;

typedef process* Process;

/* Cria um novo processo */
Process process_create (double t0, string name, double dt, double deadline);

/* Destroi o processo p */
void process_destroy (Process p);

/* Le um processo do arquivo in */
Process process_read (FILE *in);

#endif

