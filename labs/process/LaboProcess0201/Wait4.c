/*
NOM    	: Wait4.c
CLASSE 	: Process - LaboProcess 02-01
#OBJET  : réservé au Makefile
AUTEUR	: J.C. Jaumain, 07/2011
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
	pid_t pid;
	int status, i, h;
	struct rusage usage;
	if (argc < 2){
		printf("usage %s <u|s>\n", argv[0]);
		exit(1);
	}

	if (argv[1][0] == 'u') {
		if ((pid = fork()) == 0){
			srand(getpid());
			printf("pid du fils =%u\n", getpid());
			for (i = 0; i < 10000000; i++)
				sin(rand());
			exit(0);
		}
	}

	if (argv[1][0] == 's') {
		if ((pid = fork()) == 0){
			printf("pid du fils =%u\n", getpid());
			h = open("/dev/null", O_RDWR);
			for (i = 0; i < 10000000; i++)
				write(h, "a", 1);
			close(h);
			exit(0);
		}
	}
	if ((wait4(pid, &status, 0, &usage)) > 0) {
		printf("Temps utilisateur : %ld s, %ld micro sec\n",
			   usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
		printf("Temps en mode noyau : %ld s, %ld micro sec\n",
			   usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
	}
	exit(0);
}
