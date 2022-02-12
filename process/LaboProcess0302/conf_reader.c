#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    printf("Ce programme run avec l'uid %d et l'euid %d\n", getuid(), geteuid());
    execlp("cat", "cat", "Confidentiel", NULL);
    //La suite n'est jamais executé
    return 0;
}