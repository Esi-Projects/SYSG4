#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void annoy(char msg[], unsigned int n){
    for(int i = 0; i < n; i++){
        printf("%s\n", msg);
        sleep(1);
    }
}

void handler(int sig) {
    char msg[256];
    sprintf(msg, "You can't stop me even tough you sent me the signal n*%d hehehe xD\n", sig);
    write(STDOUT_FILENO, msg, strlen(msg));
    sleep(1);
}

int trapAll(){
    struct sigaction act;
    act.sa_handler = handler;
    for(int noSig = 1; noSig < 32; noSig++){
        sigaction(noSig, &act, NULL);
        signal(noSig, handler);
    }
}

int main(int argc, char * argv[]){
    unsigned int n = 0;
    if(argc != 2){
        printf("usage 'n' an integer\n");
        exit(-1);
    }

    trapAll();
    n = atoi(argv[1]);
    annoy("Do you have games on your phone ?", n);

    return 0;
}