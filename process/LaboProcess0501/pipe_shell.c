#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int rfork;
    int pipe1[2], pipe2[2];

    char ligne[257];
    printf(" Commande ?] ");
    fgets(ligne, 256, stdin);
    while (strcmp(ligne, " exit\n"))
    {
        pipe(pipe1);
        pipe(pipe2);

        if (rfork = fork() == 0)
        {
            // redirection
            dup2(pipe1[1], STDOUT_FILENO);

            // close
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[0]);
            close(pipe2[1]);

            // exec
            execlp("ps", "ps", "aux", NULL);
        }

        if (rfork = fork() == 0)
        {
            // redirection
            dup2(pipe1[0], STDIN_FILENO);
            dup2(pipe2[1], STDOUT_FILENO);

            // close
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[0]);
            close(pipe2[1]);

            // exec
            execlp("grep", "grep", "root", NULL);
        }

        if (rfork = fork() == 0)
        {
            // redirection
            dup2(pipe2[0], STDIN_FILENO);

            // close
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[0]);
            close(pipe2[1]);

            // exec
            execlp("wc", "wc", "-l", NULL);
        }

        // close
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        // wait
        while (wait(NULL) > 0)
            ;
        printf(" Commande ?] ");
        fgets(ligne, 256, stdin);
    }
    return 0;
}