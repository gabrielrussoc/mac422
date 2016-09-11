/* Descrição do Módulo 
 *
 *  Módulo responsável pela manipulação do Heap.
 *  O Heap e armazenado em um vetor, e é um heap de 
 *  mínimo que se baseia no tempo restante de um 
 *  processo para suas comparações.     
 */

#ifndef _HEAP_H
#define _HEAP_H

#include "process.h"

typedef struct {
    Process *v;
    int size;
} heap;

typedef heap* Heap;

Heap heap_create ();

void heap_destroy (Heap h);

void heap_insert (Heap h, Process p);

Process heap_getMin (Heap h); 

void heap_deleteMin (Heap h);

int heap_isempty (Heap h);


#endif 
