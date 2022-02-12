/*
NOM : Fork .c
CLASSE : Process - LaboProcess 01 -01
# OBJET : ré serv é au Makefile
AUTEUR : J. C. Jaumain , 07/2011
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// vé rifions la valeur et l ’ adresse d ’ une variable dans p è re et fils
int main()
{
    int var, r; // var est la variable en examen
    var = 6;
    printf("Avant le fork , pour le père %d , l’adresse %p contient %d\n", getpid(), (void *)&var, var);
    if ((r = fork()) == 0) {
        printf("Voici %d , fils de % d\n", getpid(), getppid());
        printf("pour % d fils de %d , l’adresse %p contient %d\n", getpid(), getppid(), (void *)&var, var);
        var = 19;
        sleep(3); // dé commenter
        printf("pour %d , fils de %d , l’adresse %p contient %d\n", getpid(), getppid(), (void *)&var, var);
        exit(0); // commenter
    }
    printf("Après le fork , pour le père %d , l’adresse %p contient %d\n", getpid(), (void *)&var, var);
    var = 13;
    // sleep (3); // d é commenter
    printf("Après le fork , pour le père %d , l’adresse %p contient %d\n", getpid(), (void *)&var, var);
    wait (0); // commenter
    exit(0);
}