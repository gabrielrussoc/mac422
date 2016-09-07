#include <stdio.h>
#include <stdlib.h>
#include "schedule.h"
#include "utility.h"

int main (int argc, char **argv) {
    if (argc > 5 || argc < 4) {
        fprintf (stderr, "Uso ./ep1 sched trace saida [d]\n");
        exit (-1);
    }
    
    g_scheduler = atoi (argv[1]);
    g_in = fopen (argv[2], "r");
    g_out = fopen (argv[3], "w");

    if (argc == 5 && argv[4][0] == 'd') g_debug = 1;
    switch (scheduler) {
        case 1:
            fcfs ();
            break;
        case 2:
            srtn ();
            break;
        default:
            fprintf (stderr, "Esse nao e um escalonador valido\n");
            break;
    }

    fclose (g_in);
    fclose (g_out);

    return 0;
}

