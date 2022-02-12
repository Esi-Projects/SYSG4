#include <stdio.h>
#include <sys/sem.h>
#include <signal.h>
#include "sem/sem_util.h"

int semIdA;
int semIdB;

void handler(int sig){
    semctl(semIdA, 0, IPC_RMID);
    semctl(semIdB, 0, IPC_RMID);
    exit(0);
}

int redirectC(){
    struct sigaction act;
    act.sa_handler = handler;
    return sigaction(SIGINT, &act, NULL);
}

int printA(){
    down(semIdA);
    printf("A");
    fflush(stdout);
    up(semIdB);
}

int main(){
    redirectC();
    semIdA = semget(SEM_A_KEY, 1, SEM_FLAG);
    semIdB = semget(SEM_A_KEY, 1, SEM_FLAG);

    semctl(semIdA, 0, SETVAL, 1);
    semctl(semIdB, 0, SETVAL,0);

    while(1){
        printA();
    }
    return 0;
}