#include <pthread.h>
#include "utility.h"
#include "queue.h"
#include "heap.h"
#include "process.h"

FILE *g_in, *g_out;
pthread_mutex_t g_tlock;    
pthread_mutex_t g_slock;
pthread_mutex_t g_dlock;
Queue g_queue;
Heap g_heap;
int g_cpu;
int g_thread;
int g_debug;
int g_context;
int g_line;
Process g_cpu_process;

void thread_wake (Process p) {
    pthread_mutex_lock (&g_tlock);
    p->paused = 0;
    pthread_cond_signal (&(p->cond));
    pthread_mutex_unlock (&g_tlock);
}

void thread_sleep (Process p) {
    pthread_mutex_lock (&g_tlock);
    p->paused = 1;
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

double elapsed () {
    return (double) clock () / CLOCKS_PER_SEC;
}

