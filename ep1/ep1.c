#include <stdio.h>
#include <stdlib.h>
#include "schedule.h"

int main (int argc, char **argv) {
    int scheduler = atoi (argv[1]);
    FILE *in = fopen (argv[2], "r");
    FILE *out = fopen (argv[3], "w");
    switch (scheduler) {
        case 1:
            fcfs (in, out);
            break;
        default:
            printf ("Esse nao e um escalonador valido\n");
            break;
    }

    return 0;
}

