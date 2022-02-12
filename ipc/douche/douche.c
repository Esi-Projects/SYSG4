#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <time.h>

int semG, semF;

int opsem(int sem, int i)
{
    int n;
    struct sembuf op[1];
    op[0].sem_num = 0; // premier et unique sémaphore
    op[0].sem_op = i;
    op[0].sem_flg = SEM_UNDO;
    if ((n = semop(sem, op, 1)) == -1)
    {
        perror("Error during semop");
        exit(1);
    }
    return (n);
}

int routineGarcon()
{
    opsem(semF, 0); // attente de zero fille
    opsem(semG, 1); // UP semGarcon
    printf("Un garcon est rentre dans la douche\n");
    opsem(semG, -1); // DOWN sem garcon
    printf("Un garcon est sortit de la douche\n");
}
int routineFille()
{
    opsem(semG, 0); // attente de zero garcon
    opsem(semF, 1); // UP semFille
    printf("Une fille est rentre dans la douche\n");
    opsem(semF, -1); // DOWN sem fille
    printf("Une fille est sortit de la douche\n");
}

int main(int argc, char *argv[])
{
    //srand(time(NULL));
    //int nbSemG = rand() % 6;
    //int nbSemF = rand() % 6;

    semG = semget(100, 1, 0666 | IPC_CREAT);
    semF = semget(200, 1, 0666 | IPC_CREAT);
    if (semG < 0 || semF < 0)
    {
        perror("Error during one of the semgets");
        exit(-1);
    }

    /*if (semctl(semG, 0, SETVAL, 0) < 0 || semctl(semF, 0, SETVAL, 0) < 0)
    {
        perror("Error during one of the semtcl");
    }*/

    int opid = getpid();
    int rfork = 0;
    for (int i = 0; i < 1000; i++){
        if (getpid() == opid){
            if ((rfork = fork()) < 0){
                perror("Error during one of the forks");
            }
        }
    }
    if (rfork == 0) {
        srand(getpid() * time(NULL));
        int r = rand() % 101;
        if (r < 50){
            routineFille();
        }else{
            routineGarcon();
        }
        exit(0);
    }else{
        while (wait(NULL) > 0);
        printf("Ending\n");
        semctl(semG, 0, IPC_RMID, 0);
        semctl(semF, 0, IPC_RMID, 0);
    }
    return 0;
}