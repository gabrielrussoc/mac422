#include <stdlib.h>

/* Biblioteca dos processos */

typedef char* string;

typedef struct {
    double t0;
    string name;
    double dt;
    double deadline;
} process;

typedef process* Process;

Process create_process (double _t0, string _name, double _dt, double _deadline);

void destroy_process (Process p);
