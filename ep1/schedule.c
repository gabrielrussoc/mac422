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
    if (g_debug) {
        pthread_mutex_lock (&g_dlock);
        fprintf (stderr, "%s acabou de executar (escrito na linha %d)\n", p->name, g_line++); 
        pthread_mutex_unlock (&g_dlock);
    }
    
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
        if (g_debug) fprintf (stderr, "CPU %d: usada por %s\n", 1, p->name); 
        thread_wake (p);
        dequeue (g_queue);
        g_thread++;
    } 
    pthread_mutex_unlock (&g_slock);
}

void fcfs () {
    Process next;
    int i = 0;
    pthread_t tid[MAX];

    g_queue = queue_create ();
    pthread_mutex_init (&g_tlock, NULL);
    pthread_mutex_init (&g_slock, NULL);
    if (g_debug) {
        pthread_mutex_init (&g_dlock, NULL);
        g_line = 0;
    }
    /*g_cpu = sysconf(_SC_NPROCESSORS_ONLN);*/
    g_cpu = 1;
    g_thread = 0;

    next = process_read (g_in);
    while (next != NULL) { 
        if (next->t0 <= elapsed ()) {
            if (g_debug) fprintf (stderr, "Novo processo: %s (lido da linha %d)\n", next->name, i);
            pthread_create (&tid[i++], NULL, do_something, next);
            pthread_mutex_lock (&g_slock);
            enqueue (g_queue, next);
            pthread_mutex_unlock (&g_slock);
            next = process_read (g_in);
        }
        next_fcfs ();
    }

    while (i) pthread_join(tid[--i], NULL);

    if (g_debug) fprintf (g_out, "%d mudanças de contexto\n", g_context);
}

/* Escalonador SRTN ////////////////////////////////////////////
///////////////////////////////////////////////////////////// */
//

void srtn () {
    Process next;
    int i = 0;
    pthread_t tid[MAX];

    g_heap = heap_create ();
    pthread_mutex_init (&g_tlock, NULL);
    pthread_mutex_init (&g_slock, NULL);
    if (g_debug) {
        pthread_mutex_init (&g_dlock, NULL);
        g_line = 0;
    }
    next = process_read (g_in);
    while (next != NULL) { 
        if (next->t0 <= elapsed ()) {
            if (g_debug) fprintf (stderr, "Novo processo: %s (lido da linha %d)\n", next->name, i);
            pthread_create (&tid[i++], NULL, do_something, next);
            pthread_mutex_lock (&g_slock);
            heap_insert (g_heap, next);
            pthread_mutex_unlock (&g_slock);
            next = process_read (g_in);
        }
        next_srtn ();
    }

    while (i) pthread_join(tid[--i], NULL);

    if (g_debug) fprintf (g_out, "%d mudanças de contexto\n", g_context);
}

static void next_strn () {
    Process p, q;
    pthread_mutex_lock (&g_slock);
    if (g_thread < g_cpu && !heap_isempty (g_heap)) {
        g_thread++;
        p = heap_getMin (g_heap);
        thread_wake (p);
        g_cpu_process = p;
        heap_deleteMin (g_heap);
    }
    else if (!heap_isempty (g_heap)) {
        p = heap_getMin (g_heap);
        q = g_cpu_process;
        if (remaining (p) < remaining (q)) {
            thread_sleep (q);
            thread_wake (p);
            g_cpu_process = p;
            heap_deleteMin (g_heap);
            heap_insert (q);
            g_context++;
        }
    }
    pthread_mutex_lock (&g_slock);
}

/* Escalonador Multiplas Filas  ////////////////////////////////
///////////////////////////////////////////////////////////// */


