/*
NOM    	: Mecho.c
CLASSE 	: intro - LaboIntro 01-04
#OBJET  : réservé au makefile
AUTEUR	: J.C. Jaumain, 07/2011
*/
/*
 * ce petit code affiche les paramètres qu'on lui passe en ligne de commande, i
 * c'est d'ailleurs ce que fait la commande echo
 * */

#include <stdlib.h>
#include <stdio.h>
main(int argc, char *argv[])
{
   int i;
   for (i = 1; i < argc - 1; i++)
   {
      printf("%s ", argv[i]); // arguments séparés d'un espace
   }
   printf("%s\n", argv[argc - 1]); // et retour à la ligne
   exit(0);
}
