#include "queue.h"
#include <stdlib.h>

Queue queue_create () {
    Queue q = malloc (sizeof (queue));
    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

void enqueue (Queue q, void *p) {
    Box new = malloc (sizeof (box));
    new->p = p;
    new->next = NULL;
    if (queue_isempty (q)) q->head = q->tail = new;  
    else { 
        q->tail->next = new;
        q->tail = new;
    }
    q->size++;
}

void dequeue (Queue q) {
    Box dead;
    if (queue_isempty (q)) return;
    dead = q->head;
    q->head = q->head->next;
    free (dead);
    q->size--;
}

void *queue_front (Queue q) {
    if (queue_isempty (q)) return NULL;
    return q->head->p;
}

int queue_isempty (Queue q) {
    return q->size == 0;
}

void queue_destroy (Queue q) {
    Box dead;
    while (q->head != NULL) {
        dead = q->head;
        q->head = q->head->next;
        free (dead);
    }
    q->tail = NULL;
    free (q);
}

