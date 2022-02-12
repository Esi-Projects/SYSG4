#NOM    : Makefile
#CLASSE : Intro - LaboIntro 01-01
#OBJET  : autour du Makefile
#HOWTO	: make; make clean
#AUTEUR	: mba 08/2016
 
# La première règle est résolue par la commande "make Test"
# c'est aussi la règle appelée par défaut car c'est la première
# elle est donc également résolue par le commande "make" sans paramètres
# Cette règle exécute "TestMake" par la commande ./TestMake 
# précédée ici par le caractère @ qui empèche l'affichage de la ligne de commande exécutée.
# Si l'exécutable n'existe pas ou n'est pas à jour, l'outil make se charge de le générer

Test:TestMake
	 @./TestMake 	

         # la commande est obligatoirement précédée d'une tabulation 
         # cela diffère d'une série d'espaces	
         # @ pour ne pas afficher la comande même

# La deuxième règle est invoquée par "make TestMake" 
# elle est également invoquée quand "TestMake" est manquant et est le prérequis d'une autre règle
# Elle sert à regénérer le fichier exécutable
# notamment, si le fichier source ou le fichier include ont été modifiés
# La commande de compilation est : gcc TestMake.c -o TestMake
# $@ notation qui désigne la cible de la règle : TestMake
# $< notation qui désigne le premier prérequis de la règle : TestMake.c

TestMake : TestMake.c  MonInclude.h
	gcc -std=c99 $< -o $@

# La troisième règle est invoquée par "make clean"
# c'est d'ailleurs la seule manière d'invoquer cette règle car la cible "clean" 
# n'apparaît nulle part comme prérequis d'une autre règle
# Elle n'a aucun prérequis non plus.

clean:
	rm -f TestMake *~
