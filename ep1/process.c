#include "process.h"
#include <stdio.h>
#include <stdlib.h>

Process create_process (double t0, string name, double dt, double deadline) {
    Process p = malloc (sizeof (process));

    p->t0 = t0;
    p->name = name;
    p->dt = dt;
    p->deadline = deadline;

    return p;
}

void destroy_process (Process p) {
    free (p->name);
    free (p);
}

Process read_process (FILE* in) {
    double t0, dt, deadline;
    string str = malloc (100 * sizeof (string));

    if (fscanf (in, "%ld %s %ld %ld", &t0, str, dt, deadline) != EOF)
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

