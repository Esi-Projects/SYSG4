/*
NOM    	: cg.c
CLASSE 	: Process - LaboProcess 03-01
#OBJET  : réservé au Makefile 
AUTEUR	: J.C. Jaumain, 07/2011
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main() {	
	int j;
	if (fork()==0) {	
		execlp("gcc","gcc","aff.c","-o","aff",0);
		printf("Erreur : gcc non trouvé\n");
		exit(1);
	}
	wait(&j);
	if (j != 0) {	
		printf("Erreur de compilation du programme aff.c\n");
		exit(1);
	}		
	execl("./aff","aff","Message",0);
	printf("Ici, vous pouvez raconter votre vie, cela ne sera jamais affiché\n");
	exit(0);
}
