#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "process.h"
#include "queue.h"

/* Para fins de comparacao de doubles */
const double EPS = 1e-9;

/* Devolve o tempo decorrido desde o inicio do programa,
 * em segundos. */
double elapsed ();



int main (int argc, char **argv) {
    FILE *in = fopen (argv[1], "r");

    Process input;
    Queue q = queue_create ();

    input = process_read (in);
    while (input != NULL || !is_empty (q)) { 
        if (input != NULL && input->t0 < elapsed () + EPS) {
            enqueue (q, input);
            printf ("botei o processo %s em %lf\n",input->name, elapsed());
            input = process_read (in);
        }
    }

    fclose (in);

    return 0;
}

double elapsed () {
    return (double) clock () / CLOCKS_PER_SEC;
}

