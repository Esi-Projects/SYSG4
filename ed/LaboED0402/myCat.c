#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[]){
    int fd;
    char c;
    if(argc < 2){
        printf("Usage <file name>\n");
        exit(-1);
    }

    fd = open(argv[1], O_RDONLY);
    while(read(fd, &c, 1) > 0){
        write(1, &c, 1);
    }
    close(fd);
}