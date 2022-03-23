#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int fd;
    char line[257];
    char *tokens[100];
    char errmsg[200];
    do
    {
        printf("$ ");
        // read input to line
        fgets(line, 256, stdin);
        if (strcmp(line, "exit\n"))
        {
            bool bg = false;
            // tokenize input
            int i = 0;
            tokens[i] = strtok(line, " \n");
            while (tokens[i] != NULL)
            {
                tokens[++i] = strtok(NULL, " \n");
            }

            if (i > 0 && (strcmp(tokens[i - 1], "&") == 0))
            {
                // bg
                bg = true;
                tokens[i - 1] = 0;
            }

            // exec
            int rfork = fork();
            if (rfork == 0)
            {
                if (i > 1 && (strcmp(tokens[i - 2], ">") == 0))
                {
                    //>
                    fd = open(tokens[i - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    tokens[i - 1] = 0;
                    tokens[i - 2] = 0;
                }
                else if (i > 1 && (strcmp(tokens[i - 2], "<") == 0))
                {
                    //<
                    fd = open(tokens[i - 1], O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    tokens[i - 1] = 0;
                    tokens[i - 2] = 0;
                }
                execvp(tokens[0], tokens);
                sprintf(errmsg, "cmd '%s' not found", tokens[0]);
                perror(errmsg);
            }
            if (bg == false)
            {
                waitpid(rfork, 0, 0);
            }
        }
    } while (strcmp(line, "exit\n"));

    return 0;
}