/*
 NOM 	: boucle.c
 CLASSE : intro - LaboIntro  01-03
 AUTEUR : MBA
 DATE	: 01/2016
*/
#include <stdlib.h>
#include <stdio.h>
#include "MonInclude.h"
#include "boucle.h"

void onBoucle (char *texte, int compt);
void onBoucle (char *texte, int compt){
	int i;
	for (i = 1; i<= compt; i++)
		printf ("%s", texte);
	printf ("\n");
}

