#include "process.h"
#include <pthread.h>
#include <stdlib.h>

Process process_create (double t0, string name, double dt, double deadline) {
    Process p = malloc (sizeof (process));

    p->t0 = t0;
    p->name = name;
    p->dt = dt;
    p->deadline = deadline;
    p->paused = 1;
    p->running = 0.;
    pthread_cond_init (&(p->cond), NULL);

    return p;
}

void process_destroy (Process p) {
    free (p->name);
    free (p);
}

Process process_read (FILE *in) {
    double t0, dt, deadline;
    string str = malloc (100 * sizeof (char));

    if (fscanf (in, "%lf %s %lf %lf", &t0, str, &dt, &deadline) != EOF)
        return process_create (t0, str, dt, deadline);

    return NULL;
}

/* Test Client 
int main () {
    Process p;
    string str;

    str = malloc (100 * sizeof (string));
    scanf ("%s", str);
    p = create_process (0, str, 3, 5);
    printf ("t0: %lf   name: %s   dt: %lf  deadline: %lf\n", p->t0, p->name, p->dt, p->deadline);
    destroy_process (p);

    str = malloc (100 * sizeof (string));
    scanf ("%s", str);
    p = create_process (1, str, 7, 10);
    printf ("t0: %lf   name: %s   dt: %lf  deadline: %lf\n", p->t0, p->name, p->dt, p->deadline);
    destroy_process (p);

    return 0;
}
*/

