/*
NOM    	: TestMake3.c
CLASSE 	: intro - LaboIntro  01-03
#OBJET  : réservé au makefile
AUTEUR	: mba 01/2016
*/
#include <stdlib.h>
#include <stdio.h>
#include "MonInclude.h"
#include "boucle.h"

int main ( int argc, char * argv[] )
{  	int i;

	if (argc < 2) exit (1);

 	sscanf(argv[1],"%d\n",&i); // convertit une représentation décimale d'un nombre 
			 	   // en sa valeur
	printf ("i=%d\n",i);
   	onBoucle ("encore ! ", i);
   	exit(0);
}
