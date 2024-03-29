#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX 1024
#define TRUE 1
#define FALSE 0

int main (int argc, char **argv) {
    char prompt[MAX], *input, *path;
    char *params[MAX], *command, *p;
    int status, i, go = TRUE;
    
    while (go == TRUE) {
        /* Exibe o prompt e le o input do usuario */
        path = getcwd (NULL, 0);
        sprintf (prompt, "(%s): ", path);
        input = readline (prompt);
        add_history (input);

        /* Separa o input em comando e parametros */
        i = 0;
        p = strtok (input, " ");
        while (p != NULL) {
            params[i++] = p;
            p = strtok (NULL, " ");
        }
        params[i] = NULL;
        command = params[0];

        /* Processa o input */
        if (command != NULL) {
            if (strcmp (command, "exit") == 0) {
                go = FALSE;
            } else if (strcmp (command, "chmod") == 0) {
                status = chmod (params[2], strtol (params[1], NULL, 8));
                if (status) perror ("Error");
            } else if (strcmp (command, "id") == 0) {
                if (strcmp (params[1], "-u") == 0) printf ("%d\n", getuid ());
            } else {
                switch (fork ()) {
                    case -1:
                        perror ("Error");
                    case 0:
                        status = execve (command, params, 0);
                        if (status) perror ("Error");
                        exit (status);
                    default:
                        waitpid (-1, &status, 0);
                }
            }
        }

        /* Limpa a memoria */
        free (input);
        free (path);
    }
    
    return EXIT_SUCCESS;
}

