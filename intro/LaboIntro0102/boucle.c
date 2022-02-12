/*
 NOM 	: boucle.c
 CLASSE : intro - LaboIntro  01-02
 AUTEUR : MBA
 DATE	: 01/2016
*/
#include <stdlib.h>
#include <stdio.h>

void onBoucle(char *texte, int compt)
{
	for (int i = 1; i <= compt; i++)
		printf("%s", texte);
	printf("\n");
}
