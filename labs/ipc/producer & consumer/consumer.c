#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include "shm/shm_util.h"
#include "sem/sem_util.h"

int semFull;
int semEmpty;
int binarySemId;

int head;

int readFromShm(char shm[]){
    while(1){
        int pid = getpid();

        opsem(semFull, -1);

        opsem(binarySemId, -1);
        //Section critique
        printf("Pid %d  Read: %d\n", pid, shm[head]);
        fflush(stdout);
        head = (head + 1) % SHM_SIZE;
        //Fin Section critique
        opsem(binarySemId, 1);

        opsem(semEmpty, 1);
    }
}

int main(){
    int shmid = shmget(SHM_KEY, SHM_SIZE, SHM_FLAG);/*get_shared_block(SHM_FILE, SHM_SIZE);*/
    char * shm = attach_memory_block(shmid);

    printf("L'adresse de la mémoire partagé est %p\n", shm);

    semEmpty = semget(SEM_KEY_EMPTY, 1, SEM_FLAG);/*get_semaphore("sem/sem_empty");*/
    semFull = semget(SEM_KEY_FULL, 1, SEM_FLAG);/*get_semaphore("sem/sem_full");*/
    binarySemId = semget(700, 1, SEM_FLAG);

    //Sets semaphores value
    set_semaphore(binarySemId, 1);

    //Sets head idx
    head = 0;

    for(int i = 0; i < 3; i++){
        int r_fork = fork();
        if(r_fork == 0){
            readFromShm(shm);
            exit(0);
        }else if(r_fork < 0){
            perror("Error during fork");
            exit(-1);
        }
    }
    
    while(wait(NULL) > 0);
    printf("End of Consumers.\n");

    //Jamais executé
    detach_memory_block(shm);
    return 0;
}