#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>

#define MAX 1024
#define TRUE 1

int octa (char *s) {
    int k = atoi(s);
    int pot = 1, ret = 0;
    while (k) {
        ret += pot*(k%10);
        k /= 10;
        pot *= 8;
    }
    return ret;
}

int main (int argc, char **argv) {
    char path[MAX], prompt[MAX], *input;
    char *params[MAX], *command, *p;
    int status, i;
    pid_t pid;
    
    while (TRUE) {
        getcwd (path, MAX);
        sprintf (prompt, "(%s): ", path);
        input = readline (prompt);

        i = 0;
        p = strtok (input, " ");
        while (p != NULL) {
            params[i++] = p;
            p = strtok (NULL, " ");
        }
        command = params[0];
        params[i] = 0;

        if (strcmp (command, "chmod") == 0) {
            chmod (params[2], octa(params[1]));
        } else if (strcmp (command, "id") == 0) {
            printf ("%d\n", getuid ());
        } else {
            switch (pid = fork()) {
                case -1:
                    fprintf (stderr, "ERRO\n");
                    exit(EXIT_FAILURE);
                case 0:
                    status = execve (command, params, 0);
                    exit (status);
                default:
                    waitpid (pid, &status, 0);
            }
        }
    }
    
    return 0;
}
