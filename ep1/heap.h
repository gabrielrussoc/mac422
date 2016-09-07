#ifndef _HEAP_H
#define _HEAP_H

#include "process.h"

typedef struct {
    Process *v;
    int size;
    int N;
} heap;

typedef heap* Heap;

Heap heap_create ();

void heap_destroy (Heap h);

void heap_insert (Heap h, Process p);

Process heap_getMin (Heap h); 

void heap_deleteMin (Heap h);

int heap_isempty (Heap h);


#endif 
