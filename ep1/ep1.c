#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"
#include "utility.h"

int main (int argc, char **argv) {
    int scheduler = atoi (argv[1]);
    FILE *in = fopen (argv[2], "r");
    FILE *out = fopen (argv[3], "w");

    if (argc == 5 && strcmp (argv[5], "d") == 0) g_debug = 1;
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

