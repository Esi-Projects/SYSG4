#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    int rfork = fork();

    if(rfork == 0){
        int rfork2 = fork();
        if(rfork2 == 0){
            printf("I am the process %d my parent is %d, I will sleep now\n", getpid(), getppid());
            sleep(3);
            //here this process has been adopted
            printf("I am the process %d my parent is %d, I just woke up\n", getpid(), getppid());
            exit(0);
        }

        printf("I am the process %d my parent is %d, I will die now\n", getpid(), getppid());
        printf("I didn't check on %d, he will be adopted by init\n", rfork2);
        sleep(1);
        //this process died without waiting his child
        exit(0);
    }

  
    sleep(1);
    char cmd[256];
    sprintf(cmd, "ps");
    system(cmd);    


    int childid = wait(NULL);
    printf("I am the parent %d I checked on %d, he can rest in peace now\n", getpid(), childid);
    return 0;
}