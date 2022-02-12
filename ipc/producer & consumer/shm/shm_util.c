#include "shm_util.h"

int get_shared_block(char filename[], int size){
    int key = ftok(filename, 0);
    if(key < 0){
        perror("Error during ftok");
    }
    int shmid = shmget(key, size, 0666 | IPC_CREAT);
    if(shmid < 0){
        perror("Error during shmget");
    }
    return shmid;
}

char * attach_memory_block(int shmid){
    char * shm = shmat(shmid, 0, 0666);
    if(shm < 0){
        perror("Error during shmat");
    }
    return shm;
}

void detach_memory_block(char * shm){
    int r = shmdt(shm);
    if(r < 0){
        perror("Error during shmdt");
    }
}

void delete_shared_block(int shmid){
    int r = shmctl(shmid, IPC_RMID, NULL);
    if(r < 0){
        perror("Error during shmdt");
    }
}