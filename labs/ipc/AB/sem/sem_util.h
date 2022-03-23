#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define SEM_A_KEY 65
#define SEM_B_KEY 66
#define SEM_FLAG (0666 | IPC_CREAT)

int down(int semid);
int up(int semid);
