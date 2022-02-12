#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_FILE "shm/shm_file"
#define SHM_KEY 100
#define SHM_SIZE 10
#define SHM_FLAG (0666 | IPC_CREAT)

int get_shared_block(char filename[], int size);

char * attach_memory_block(int shmid);

void detach_memory_block(char * shm);

void delete_shared_block(int shmid);