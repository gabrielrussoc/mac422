#include <stdio.h>
#include "schedule.h"

int main (int argc, char **argv) {
    FILE *in = fopen (argv[1], "r");
    fcfs (in);
}

