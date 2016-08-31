#include "process.h"
#include <stdio.h>

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

/* Test Client */
int main () {
    Process p;
    string str;

    /* Process 0 */
    str = malloc (100 * sizeof (string));
    scanf ("%s", str);
    p = create_process (0, str, 3, 5);
    printf ("t0: %lf   name: %s   dt: %lf  deadline: %lf\n", p->t0, p->name, p->dt, p->deadline);
    destroy_process (p);

    /* Process 1 */
    str = malloc (100 * sizeof (string));
    scanf ("%s", str);
    p = create_process (1, str, 7, 10);
    printf ("t0: %lf   name: %s   dt: %lf  deadline: %lf\n", p->t0, p->name, p->dt, p->deadline);
    destroy_process (p);

    return 0;
}

