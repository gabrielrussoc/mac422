#include "heap.h"
#include <stdlib.h>

static int MAX = 2;

/* Static Functions */
static void reallocMem (Process *v, int size);
static void siftUp (Heap h);
static void siftDown (Heap h);

Heap heap_create () {
    Heap h = malloc (sizeof (heap));
    h->size = 0;
    h->v = malloc (MAX * sizeof (h->v)); 

    return h;
}

void heap_destroy (Heap h) {
    free (h->v);
    free (h);
}

void heap_insert (Heap h, Process p) {
    h->size++;
    if (h->size == MAX) reallocMem (h->v, MAX*2);
    h->v[h->size] = p;
    siftUp (h);
}

Process heap_getMin (Heap h) {
    if (is_empty (h)) return NULL;
    return h->v[1];
}

void heap_deleteMin (Heap h) {
    if (is_empty (h)) return;
    /* Faz isso? destroy_process (h->v[1]);*/
    h->v[1] = h->v[h->size];
    h->size--;
    if (h->size < 1/4 * MAX) reallocMem (h->v, MAX/2);
    siftDown (h);
}

int is_empty (Heap h) {
    return h->size == 0;
}

static void reallocMem (Process *v, int size) {
    MAX = size;
    realloc (v, MAX);
}

static void siftUp (Heap h) {
    int f = h->size, p = f / 2;
    Process t = h->v[f];
    while (p >= 1) {
        if (t->dt > h->v[p]->dt) break;
        h->v[f] = h->v[p];
        f = p;
        p = f / 2;
    }
    h->v[f] = t;

}

static void siftDown (Heap h) {
    int p = 1, f = 2;
    Process t = h->v[1];
    while (f <= h->size) {
        if (f < h->size && h->v[f]->dt > h->v[f+1]->dt) f++;
        if (t->dt < h->v[f]->dt) break;
        h->v[p] = h->v[f];
        p = f; f = 2*p;
    }
    h->v[p] = t;
}

/* Test Client 
int main () {
    Heap h = heap_create ();
    int i;
    for (i = 0; i < 5; i++) {
        Process p = process_read (stdin);
        heap_insert (h, p);
    }
    for (i = 0; i < 5; i++) {
        printf ("%f\n", heap_getMin (h)->dt);
        heap_deleteMin (h);
    }
}
*/
