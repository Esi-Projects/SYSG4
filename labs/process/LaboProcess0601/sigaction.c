#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

//var
struct sigaction act;

void annoy(char msg[], unsigned int n){
    for(int i = 0; i < n; i++){
        printf("%s\n", msg);
        sleep(1);
    }
}

void handler(int sig) {
    char msg[256];
    sprintf(msg, "J'ai compris :(\n");
    write(STDOUT_FILENO, msg, strlen(msg));

    //Ignore les prochains signaux d'interruptions
    act.sa_handler = SIG_IGN;
    sigaction(SIGINT, &act, NULL);

    sleep(1);
    exit(0); 
}

int trapInt(){
    act.sa_handler = handler;
    sigaction(SIGINT, &act, NULL);
    
}

int main(int argc, char * argv[]){
    unsigned int n = 0;
    if(argc != 2){
        printf("utilisation 'n' un entier\n");
        exit(-1);
    }

    trapInt();
    n = atoi(argv[1]);
    annoy("Je peux jouer sur ton telephone ?", n);

    return 0;
}