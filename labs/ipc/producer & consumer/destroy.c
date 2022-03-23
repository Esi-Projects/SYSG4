#include "shm/shm_util.h"
#include "sem/sem_util.h"

int main(){

    //get shared memory id
    int shmid = shmget(SHM_KEY, SHM_SIZE, SHM_FLAG);

    //get semaphores id
    int semEmpty = semget(SEM_KEY_EMPTY, 1, SEM_FLAG);
    int semFull = semget(SEM_KEY_FULL, 1, SEM_FLAG);
    int binarySemIdProducer = semget(700, 1, SEM_FLAG);
    int binarySemIdConsumer = semget(800, 1, SEM_FLAG);

    //destroy shared memory
    delete_shared_block(shmid);

    //destroy semaphores
    destroy_semaphore(semEmpty);
    destroy_semaphore(semFull);
    destroy_semaphore(binarySemIdProducer);
    destroy_semaphore(binarySemIdConsumer);
}
