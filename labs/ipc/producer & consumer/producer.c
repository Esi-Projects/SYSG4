#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "shm/shm_util.h"
#include "sem/sem_util.h"

int semFull;
int semEmpty;
int binarySemId;

int tail;

int writeToShm(char shm[]){
    while(1){  
        srand(getpid() * time(NULL));
        char val = rand() % 128;
        int pid = getpid();

        opsem(semEmpty, -1);

        opsem(binarySemId, -1);
        //Section critique
        shm[tail] = val;
        printf("Pid %d Wrote: %d or %d\n", pid, val, shm[tail]);
        fflush(stdout);
        tail = (tail + 1) % SHM_SIZE;
        //Fin Section critique
        opsem(binarySemId, 1);

        opsem(semFull, 1);
        sleep(0.5);
    }
}

int main(){
    int shmid = shmget(SHM_KEY, SHM_SIZE, SHM_FLAG);/*get_shared_block(SHM_FILE, SHM_SIZE);*/
    char * shm = attach_memory_block(shmid);

    printf("L'adresse de la mémoire partagé est %p\n", shm);

    semEmpty = semget(SEM_KEY_EMPTY, 1, SEM_FLAG);/*get_semaphore("sem/sem_empty");*/
    semFull = semget(SEM_KEY_FULL, 1, SEM_FLAG);/*get_semaphore("sem/sem_full");*/
    binarySemId = semget(800, 1, SEM_FLAG);

    //Sets semaphores value
    set_semaphore(semEmpty, SHM_SIZE);
    set_semaphore(semFull, 0);
    set_semaphore(binarySemId, 1);

    //Set tail idx
    tail = 0;

    for(int i = 0; i < 3; i++){
        int r_fork = fork();
        if(r_fork == 0){
            writeToShm(shm);
            exit(0);
        }else if(r_fork < 0){
            perror("Error during fork");
            exit(-1);
        }
    }
    
    while(wait(NULL) > 0);
    printf("End of Producers.\n");
    

    //Jamais executé
    detach_memory_block(shm);
    return 0;
}