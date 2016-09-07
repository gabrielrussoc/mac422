#include "heap.h"
#include <stdlib.h>

static int N = 2;

/* Static Functions */
static void reallocMem (Process *v, int size);
static void siftUp (Heap h);
static void siftDown (Heap h);

Heap heap_create () {
    Heap h = malloc (sizeof (heap));
    h->size = 0;
    h->v = malloc (N * sizeof (h->v)); 

    return h;
}

void heap_destroy (Heap h) {
    free (h->v);
    free (h);
}

void heap_insert (Heap h, Process p) {
    h->size++;
    if (h->size == N) reallocMem (h->v, N*2);
    h->v[h->size] = p;
    siftUp (h);
}

Process heap_getMin (Heap h) {
    if (heap_isempty (h)) return NULL;
    return h->v[1];
}

void heap_deleteMin (Heap h) {
    if (heap_isempty (h)) return;
    h->v[1] = h->v[h->size];
    h->size--;
    if (h->size < 1/4 * N) reallocMem (h->v, N/2);
    siftDown (h);
}

int heap_isempty (Heap h) {
    return h->size == 0;
}

static void reallocMem (Process *v, int size) {
    N = size;
    realloc (v, N);
}

static void siftUp (Heap h) {
    int f = h->size, p = f / 2;
    Process t = h->v[f];
    while (p >= 1) {
        if (process_remaining (t) > process_remaining (h->v[p])) break;
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
        if (f < h->size && process_remaining (h->v[f]) > process_remaining (h->v[f+1])) f++;
        if (process_remaining (t) < process_remaining (h->v[f])) break;
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
