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

/* Cria um novo processo */
Process create_process (double t0, string name, double dt, double deadline);

/* Destroi o processo p */
void destroy_process (Process p);
