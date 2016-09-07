#include "schedule.h"
#include "process.h"
#include "queue.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *do_something (void *a) {
    Process p = a;
    int foo = 1;
    double aux, start, idle;
    start = elapsed ();
    idle = 0;
    while (p->running < p->dt) {
        aux = elapsed ();
        thread_check (p);
        idle += elapsed () - aux; 
        foo = foo * 1;
        p->running = elapsed () - start - idle;
    }

    pthread_mutex_lock (&queue_lock);
    n_thread--;
    pthread_mutex_unlock (&queue_lock);


    aux = elapsed ();
    fprintf (g_out, "%s %lf %lf\n", p->name, aux, aux - p->t0);
    printf ("%s acabou com %lf\n", p->name, elapsed ());
    
    next_fcfs ();
    pthread_exit (NULL);
}

/* Escalonador FCFS ////////////////////////////////////////////
///////////////////////////////////////////////////////////// */

/* Escolhe a proxima thread a ser executada no algoritmo FCFS */
static void next_fcfs () {
    Process p;
    pthread_mutex_lock (&queue_lock);
    if (n_thread < n_cpu && !queue_isempty (q)) {
        p = queue_front (q);
        printf ("Rodei %s com %lf\n", p->name, elapsed());
        thread_wake (queue_front (q));
        dequeue (q);
        n_thread++;
    } 
    pthread_mutex_unlock (&queue_lock);
}

void fcfs (FILE *in, FILE *out) {
    g_out = out;
    Process next;
    int i = 0;
    pthread_t tid[123];

    q = queue_create ();
    pthread_mutex_init (&thread_lock, NULL);
    pthread_mutex_init (&queue_lock, NULL);
    /*n_cpu = sysconf(_SC_NPROCESSORS_ONLN);*/
    n_cpu = 1;
    n_thread = 0;

    next = process_read (in);
    while (next != NULL) { 
        if (next->t0 <= elapsed ()) {
            printf ("Chegou %s em %lf\n", next->name, elapsed ());
            pthread_create (&tid[i++], NULL, do_something, next);
            pthread_mutex_lock (&queue_lock);
            enqueue (q, next);
            pthread_mutex_unlock (&queue_lock);
            next = process_read (in);
        }
        next_fcfs ();
    }

    while (i) pthread_join(tid[--i], NULL);

    fprintf ("%d\n", g_context);
}

/* Escalonador SRTN ////////////////////////////////////////////
///////////////////////////////////////////////////////////// */

/* Escalonador Multiplas Filas  ////////////////////////////////
///////////////////////////////////////////////////////////// */


