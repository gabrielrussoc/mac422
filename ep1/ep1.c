#include <stdio.h>
#include <process.h>


int main (int argc, string* argv) {
    FILE *in = fopen (argv[1], "r");

    Process input;
    Queue q = queue_create ();

    input = read_process (in);
    while (input != NULL && !is_empty (q)) { 
        if (input != NULL && input->t0 >= time ()) {
            enqueue (q, input);
            input = read_process (in);
        }
        magica ();
    }

    fclose (in);

    return 0;
}
