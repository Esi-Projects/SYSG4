#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    char line[257];
    char * tokens [100];
    char errmsg [200];
    do{
        printf("$ ");
        //read input to line
        fgets ( line ,256 , stdin);
        if(strcmp(line, "exit\n")){
            //tokenize input
            int i = 0;
            tokens[i] = strtok(line, " \n");
            while (tokens[i] != NULL){
                tokens[++i] = strtok(NULL, " \n");
            }
            
            //exec
            if(fork() == 0){
                execvp(tokens[0], tokens);
                sprintf(errmsg, "cmd '%s' not found" , tokens [0]);
                perror (errmsg);
            }
            wait(0);
        }
    }while(strcmp(line, "exit\n"));
    
    return 0;   
}