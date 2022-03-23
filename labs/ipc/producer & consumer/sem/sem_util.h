#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define SEM_KEY_FULL 600
#define SEM_KEY_EMPTY 500
#define SEM_FLAG (0666 | IPC_CREAT)

int get_semaphore(char filename[]);

void destroy_semaphore(int semid);

void set_semaphore(int semid, int value);

int opsem(int sem, int i);

