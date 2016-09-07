#include <pthread.h>
#include "utility.h"
#include "queue.h"
#include "heap.h"

FILE *g_in, *g_out;
pthread_mutex_t g_tlock;    
pthread_mutex_t g_slock;
Queue g_queue;
Heap g_heap;
int g_cpu;
int g_thread;
int g_debug;

void thread_wake (Process p) {
    pthread_mutex_lock (&thread_lock);
    p->paused = 0;
    pthread_cond_signal (&(p->cond));
    pthread_mutex_unlock (&thread_lock);
}

void thread_sleep (Process p) {
    pthread_mutex_lock (&thread_lock);
    p->paused = 1;
    pthread_mutex_unlock (&thread_lock);
}

void thread_check (Process p) {
    pthread_mutex_lock (&thread_lock);
    while (p->paused)
        pthread_cond_wait (&(p->cond), &thread_lock);
    pthread_mutex_unlock (&thread_lock);
}

double elapsed () {
    return (double) clock () / CLOCKS_PER_SEC;
}

