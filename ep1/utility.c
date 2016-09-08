#include <pthread.h>
#include "utility.h"
#include "queue.h"
#include "heap.h"
#include "process.h"

FILE *g_in, *g_out;
pthread_mutex_t g_tlock;    
pthread_mutex_t g_slock;
Queue g_queue;
Heap g_heap;
Queue *g_multi_queue;
int g_cpu;
int g_thread;
int g_debug;
int g_context;
int g_line;
Process g_cpu_process;
int g_scheduler;

void thread_wake (Process p) {
    pthread_mutex_lock (&g_tlock);
    p->paused = FALSE;
    pthread_cond_signal (&(p->cond));
    pthread_mutex_unlock (&g_tlock);
}

void thread_sleep (Process p) {
    pthread_mutex_lock (&g_tlock);
    p->paused = TRUE;
    pthread_mutex_unlock (&g_tlock);
}

double thread_check (Process p) {
    double s, t;
    s = t = elapsed ();
    pthread_mutex_lock (&g_tlock);
    while (p->paused) {
        pthread_cond_wait (&(p->cond), &g_tlock);
        t = elapsed ();
    }
    pthread_mutex_unlock (&g_tlock);

    return t - s;
}

void mutex_init () {
   pthread_mutex_init (&g_tlock, NULL);
    pthread_mutex_init (&g_slock, NULL);
    if (g_debug) {
        pthread_mutex_init (&g_dlock, NULL);
        g_line = 0;
    }
}

void mutex_destroy () {
    pthread_mutex_destroy (&g_tlock);
    pthread_mutex_destroy (&g_slock);
    if (g_debug) pthread_mutex_destroy (&g_dlock);
}

double elapsed () {
    return (double) clock () / CLOCKS_PER_SEC;
}

