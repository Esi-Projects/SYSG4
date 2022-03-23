#include "sem_util.h"

int down(int semid){
    struct sembuf ops[1];
    ops[0].sem_num = 0;
    ops[0].sem_op = -1;
    ops[0].sem_flg = SEM_UNDO;
    semop(semid, ops, 1);
}

int up(int semid){
    struct sembuf ops[1];
    ops[0].sem_num = 0;
    ops[0].sem_op = +1;
    ops[0].sem_flg = SEM_UNDO;
    semop(semid, ops, 1);
}