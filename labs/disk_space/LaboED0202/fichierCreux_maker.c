#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
    char buff[] = "Hi";
    int fd = open("fichier_creux", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if( fd < 0){
        perror("fichier_creux");
        exit (1);
    }
    write(fd, buff, strlen(buff));
    lseek(fd, 40960, SEEK_CUR);
    write(fd, buff, strlen(buff));
    close(fd);
    return 0;
}

int main()
{
    displayDir(".");
}