#include "schedule.h"
#include "process.h"
#include "queue.h"
#include "utility.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/* Escolhe a proxima thread a ser executada no algoritmo FCFS */
static void next_fcfs ();

void *do_something (void *a) {
    Process p = a;
    int foo = 1;
    double aux, start, idle;
    start = elapsed ();
    idle = 0;
    while (p->running < p->dt) {
        idle += thread_check (p);
        foo = foo * 1;
        p->running = elapsed () - start - idle;
    }

    pthread_mutex_lock (&g_slock);
    g_thread--;
    pthread_mutex_unlock (&g_slock);


    aux = elapsed ();
    fprintf (g_out, "%s %lf %lf\n", p->name, aux, aux - p->t0);
    printf ("%s acabou com %lf\n", p->name, elapsed ());
    
    next_fcfs ();
    pthread_exit (NULL);
}

/* Escalonador FCFS ////////////////////////////////////////////
///////////////////////////////////////////////////////////// */

static void next_fcfs () {
    Process p;
    pthread_mutex_lock (&g_slock);
    if (g_thread < g_cpu && !queue_isempty (g_queue)) {
        p = queue_front (g_queue);
        printf ("Rodei %s com %lf\n", p->name, elapsed());
        thread_wake (p);
        dequeue (g_queue);
        g_thread++;
    } 
    pthread_mutex_unlock (&g_slock);
}

void fcfs () {
    Process next;
    int i = 0;
    pthread_t tid[123];

    g_queue = queue_create ();
    pthread_mutex_init (&g_tlock, NULL);
    pthread_mutex_init (&g_slock, NULL);
    /*g_cpu = sysconf(_SC_NPROCESSORS_ONLN);*/
    g_cpu = 1;
    g_thread = 0;

    next = process_read (g_in);
    while (next != NULL) { 
        if (next->t0 <= elapsed ()) {
            printf ("Chegou %s em %lf\n", next->name, elapsed ());
            pthread_create (&tid[i++], NULL, do_something, next);
            pthread_mutex_lock (&g_slock);
            enqueue (g_queue, next);
            pthread_mutex_unlock (&g_slock);
            next = process_read (g_in);
        }
        next_fcfs ();
    }

    while (i) pthread_join(tid[--i], NULL);

    fprintf (g_out, "%d\n", g_context);
}

/* Escalonador SRTN ////////////////////////////////////////////
///////////////////////////////////////////////////////////// */

/* Escalonador Multiplas Filas  ////////////////////////////////
///////////////////////////////////////////////////////////// */


