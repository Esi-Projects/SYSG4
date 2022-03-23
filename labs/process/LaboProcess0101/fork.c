#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int myVar = 0;
    int * myPvar = malloc(sizeof(int));
    int rfork = fork();

    if(rfork < 0){
        perror("Error during the fork");
        exit(-1);
    }

    /*if(rfork == 0){
        myVar -= 999;
        printf("Je suis le process enfant\n");
        printf("Pid %d my var: %d my var address: %p\n", getpid(), myVar, &myVar);
    }else{
        myVar += 999;
        printf("Je suis le process parent\n");
        printf("Pid %d my var: %d my var address: %p\n", getpid(), myVar, &myVar);
    }*/

    if(rfork == 0){
        *myPvar -= 69;
        printf("Je suis le process enfant\n");
        printf("Pid %d | the value of the address stored in the pointer: %d\n", getpid(), *myPvar);
        printf("Pid %d | the address stored in the pointer: %p\n", getpid(), myPvar);
    }else{
        *myPvar += 96;
        printf("Je suis le process parent\n");
        printf("Pid %d | the value of the address stored in the pointer: %d\n", getpid(), *myPvar);
        printf("Pid %d | the address stored in the pointer: %p\n", getpid(), myPvar);
    }

    wait(NULL);
    return 0;
}