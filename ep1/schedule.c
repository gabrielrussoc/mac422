#include "schedule.h"
#include "process.h"
#include "queue.h"
#include "utility.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/* TODO 
 * e se tirassemos o g_thread mandando o next somente quando for necessario e nao sempre
 * tirar lf
 * Checar memoria
 * Escalonador multiplas filas: variavel global que marca o tempo do cara 
 *  na cpu, dai no next ele verfica isso e pausa o maluco 
 *  temos ele tbm, entao podemos dar enqueue na fila certa
 *  um sinal pro next_multilevel que vai ser um while nao vazio fica 
 *  rodando entre as filas e so manda quando o sinal chegar quando ler um cara chama
 *  next 
 *  problema, se fizer separado do multilevel nao vamos inseririr os processo sna hor
 *  que chegam
 * */

/* Escolhe a proxima thread a ser executada no algoritmo FCFS */
static void next_fcfs ();

/* Escolhe a proxima thread a ser executada no algoritmo SRTN */
static void next_srtn ();

/* Escolhe a proxima thread a ser executada no algoritmo de 
 * escalonamento com multiplas filas */
static void next_multilevel ();

/* Escolhe a proxima thread a ser executada com base no algoritmo
 * de escalonamento que está rodando (g_scheduler) */
static void next_process ();

static void next_process () {
    switch (g_scheduler) {
        case 1:
            next_fcfs ();
            break;
        case 2:
            next_srtn ();
            break;
        case 3:
            next_multilevel ();
            break;
    }
}

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

    aux = elapsed ();
    fprintf (g_out, "%s %f %f\n", p->name, aux, aux - p->t0);
    if (g_debug) {
        pthread_mutex_lock (&g_dlock);
        fprintf (stderr, "[%.3f] %s acabou de executar (escrito na linha %d)\n", elapsed (), p->name, g_line++); 
        pthread_mutex_unlock (&g_dlock);
    }

    pthread_mutex_lock (&g_slock);
    g_thread--;
    pthread_mutex_unlock (&g_slock);
    
    next_process ();
    process_destroy (p);
    pthread_exit (NULL);
}

/* Escalonador FCFS ////////////////////////////////////////////
///////////////////////////////////////////////////////////// */

void fcfs () {
    Process next;
    int i = 0;
    pthread_t tid[MAX];

    g_queue = queue_create ();
    mutex_init ();
   /*g_cpu = sysconf(_SC_NPROCESSORS_ONLN);*/
    g_cpu = 1;
    g_thread = 0;

    next = process_read (g_in);
    while (next != NULL) { 
        if (next->t0 <= elapsed ()) {
            if (g_debug) fprintf (stderr, "[%.3f] Novo processo: %s (lido da linha %d)\n", elapsed (), next->name, i);
            pthread_create (&tid[i++], NULL, do_something, next);
            pthread_mutex_lock (&g_slock);
            enqueue (g_queue, next);
            pthread_mutex_unlock (&g_slock);
            next = process_read (g_in);
        }
        next_fcfs ();
    }

    while (i) pthread_join(tid[--i], NULL);
    queue_destroy (g_queue);
    mutex_destroy ();

    if (g_debug) fprintf (stderr, "[%.3f] %d mudanças de contexto\n", elapsed (), g_context);
    fprintf (g_out, "%d mudanças de contexto\n", g_context);
}

static void next_fcfs () {
    Process p;
    pthread_mutex_lock (&g_slock);
    if (g_thread < g_cpu && !queue_isempty (g_queue)) {
        p = queue_front (g_queue);
        if (g_debug) fprintf (stderr, "[%.3f] CPU %d: usada por %s\n", elapsed (), 1, p->name); 
        thread_wake (p);
        dequeue (g_queue);
        g_thread++;
    } 
    pthread_mutex_unlock (&g_slock);
}


/* Escalonador SRTN ////////////////////////////////////////////
///////////////////////////////////////////////////////////// */

void srtn () {
    Process next;
    int i = 0;
    pthread_t tid[MAX];

    g_heap = heap_create ();
    mutex_init ();
    /*g_cpu = sysconf(_SC_NPROCESSORS_ONLN);*/
    g_cpu = 1;
    g_thread = 0;

    next = process_read (g_in);
    while (next != NULL) { 
        if (next->t0 <= elapsed ()) {
            if (g_debug) fprintf (stderr, "[%.3f] Novo processo: %s (lido da linha %d)\n", elapsed (), next->name, i);
            pthread_create (&tid[i++], NULL, do_something, next);
            pthread_mutex_lock (&g_slock);
            heap_insert (g_heap, next);
            pthread_mutex_unlock (&g_slock);
            next = process_read (g_in);
        }
        next_srtn ();
    }

    while (i) pthread_join(tid[--i], NULL);
    heap_destroy (g_heap);
    mutex_destroy ();

    if (g_debug) fprintf (stderr, "[%.3f] %d mudanças de contexto\n", elapsed (), g_context);
    fprintf (g_out, "%d mudanças de contexto\n", g_context);
}

static void next_srtn () {
    Process p, q;
    pthread_mutex_lock (&g_slock);
    if (g_thread < g_cpu && !heap_isempty (g_heap)) {
        g_thread++;
        p = heap_getMin (g_heap);
        if (g_debug) fprintf (stderr, "[%.3f] CPU %d: usada por %s\n", elapsed (), 1, p->name); 
        thread_wake (p);
        g_cpu_process = p;
        heap_deleteMin (g_heap);
    }
    else if (!heap_isempty (g_heap)) {
        p = heap_getMin (g_heap);
        q = g_cpu_process;
        if (process_remaining (p) < process_remaining (q)) {
            if (g_debug) fprintf (stderr, "[%.3f] CPU %d: liberada por %s\n", elapsed (), 1, q->name); 
            thread_sleep (q);
            if (g_debug) fprintf (stderr, "[%.3f] CPU %d: usada por %s\n", elapsed (), 1, p->name); 
            thread_wake (p);
            g_cpu_process = p;
            heap_deleteMin (g_heap);
            heap_insert (g_heap, q);
            g_context++;
        }
    }
    pthread_mutex_unlock (&g_slock);
}

/* Escalonador Multiplas Filas  ////////////////////////////////
///////////////////////////////////////////////////////////// */

void multilevel () 
    Process next;
    int i = 0;
    pthread_t tid[MAX];

    /* Criar vetor de filas */
    multilevel_init (); 
    mutex_init ();

    /* Inicializacao de variaveis */`
    /*g_cpu = sysconf(_SC_NPROCESSORS_ONLN);*/
    g_cpu = 1;
    g_thread = 0;

    next = process_read (g_in);
    while (next != NULL) { 
        if (next->t0 <= elapsed ()) {
            if (g_debug) fprintf (stderr, "[%.3f] Novo processo: %s (lido da linha %d)\n", elapsed (), next->name, i);
            pthread_create (&tid[i++], NULL, do_something_else, next);
            pthread_mutex_lock (&g_slock);
            enqueue (g_muli_queues[next->class], next);
            pthread_mutex_unlock (&g_slock);
            next_multilevel ();
            next = process_read (g_in);
        }
    }

    while (i) pthread_join(tid[--i], NULL);
    /* Destroi vetor de filas */
    multilevel_destroy ();
    mutex_destroy ();

    if (g_debug) fprintf (stderr, "[%.3f] %d mudanças de contexto\n", elapsed (), g_context);
    fprintf (g_out, "%d mudanças de contexto\n", g_context);
}

void next_multilevel () {
    /* pensando que eu tenho globalmente a fila que eu retirei o ultimo processo */
    Process p;
    int i;


    pthread_mutex_lock (&g_slock);
    for (i = 0; i < g_nqueues; i++) 
        if (!queue_isempty (g_multi_queues[i])) break;
    if (i != q_nqueue) {
        p = queue_front (g_multi_queues[i]);
        if (g_debug) fprintf (stderr, "[%.3f] CPU %d: usada por %s\n", elapsed (), 1, p->name); 
        thread_wake (p);

        g_thread++;

        dequeue (g_multi_queue[i]);
    }
    pthread_mutex_unlock (&g_slock);

}

void *do_something_else (void *a) {
    Process p = a;
    int foo = 1;
    double aux, start, idle;
    start = elapsed ();
    idle = aux = 0;

    while (p->running < p->dt) {
        idle += thread_check (p);
        foo = foo * 1;
        p->running = elapsed () - start - idle;
        if (p->running - aux  > process_quantum (p)) {
            thread sleep (p);
            aux = p->running;
            p->class = (p->class + 1) % g_nqueues; 
            pthread_mutex_lock (&g_slock);
            enqueue (q_multi_queues[p->class], p);
            pthread_mutex_unlock (&g_slock);
            next_multilevel ();
        }
    }

    aux = elapsed ();
    fprintf (g_out, "%s %f %f\n", p->name, aux, aux - p->t0);
    if (g_debug) {
        pthread_mutex_lock (&g_dlock);
        fprintf (stderr, "[%.3f] %s acabou de executar (escrito na linha %d)\n", elapsed (), p->name, g_line++); 
        pthread_mutex_unlock (&g_dlock);
    }
    next_multilevel ();

    pthread_mutex_lock (&g_slock);
    g_thread--;
    pthread_mutex_unlock (&g_slock);

    next_process ();
    process_destroy (p);
    pthread_exit (NULL);
}

static void multi_init () {
    int i;
    for (i = 0; i < g_nqueues; i++) 
        g_multi_queues[i] = queue_create (); 
}
static void multi_destroy () {
    int i;
    for (i = 0; i < g_nqueues; i++) 
        queue_destroy (g_multi_queues[i]; 
