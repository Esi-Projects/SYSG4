#include "sem_util.h"

int get_semaphore(char filename[]){
    int key = ftok(filename, 0);
    if(key < 0){
        perror("Error during ftok");
    }
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    if(semid < 0){
        perror("Error during semget");
        exit(-1);
    }
    return semid;
}

void destroy_semaphore(int semid){
    int r = semctl(semid, 0, IPC_RMID, NULL);
    if(r < 0){
        perror("Error during semctl");
        exit(-1);
    }
}

void set_semaphore(int semid, int value){
    int r = semctl(semid, 0, SETVAL, value);
    if(r < 0){
        perror("Error during semctl");
        exit(-1);
    }
}

int opsem(int semid, int i) {
    int n;
    struct sembuf op[1];
    op[0].sem_num = 0; // premier et unique sémaphore
    op[0].sem_op = i;
    op[0].sem_flg = SEM_UNDO;
    if ((n = semop(semid, op, 1)) == -1) {
        perror("Error during semop");
        exit(-1);
    }
    return (n);
}
