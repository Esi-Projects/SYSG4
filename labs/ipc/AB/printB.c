#include <stdio.h>
#include <sys/sem.h>
#include <signal.h>
#include "sem/sem_util.h"

int semIdA;
int semIdB;

int printB(){
    down(semIdB);
    printf("B");
    fflush(stdout);
    up(semIdA);
}

int main(){
    semIdA = semget(SEM_A_KEY, 1, SEM_FLAG);
    semIdB = semget(SEM_A_KEY, 1, SEM_FLAG);

    while(1){
        printB();
    }
    return(0);
}