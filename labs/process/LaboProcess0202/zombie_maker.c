#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    int rfork = fork();
    if(rfork == -1){
        perror("Error during the fork");
    }

    if(rfork == 0){
        printf("I am the process %d my parent is %d, I will die now\n", getpid(), getppid());
        exit(0);
    }

  
    char cmd[256];
    sprintf(cmd, "ps | grep %d", rfork);
    system(cmd);    


    int childid = wait(NULL);
    printf("I am the parent %d I checked on %d, he can rest in peace now\n", getpid(), childid);
    
    return 0;
}