#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct bo {
    void *p;
    struct bo *next;
} box;
typedef box* Box;

typedef struct {
    Box head, tail;
    int size;
} queue;
typedef queue* Queue;

/* Cria uma nova fila */
Queue queue_create ();

/* Destroi a fila q */
void queue_destroy (Queue q);

/* Enfileira p na fila q */
void enqueue (Queue q, void *p);

/* Desenfileira o primeiro elemento de q */
void dequeue (Queue q);

/* Devolve o primeiro elemento de q */
void *queue_front (Queue q);

/* Devolve 1 se a fila q esta vazia ou 0 caso contraio */
int queue_isempty (Queue q);

#endif

