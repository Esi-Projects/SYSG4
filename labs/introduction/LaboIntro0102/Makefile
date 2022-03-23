#NOM    : Makefile
#CLASSE : Intro - LaboIntro 01-02
#OBJET  : autour du Makefile
#HOWTO	: make
#AUTEUR	: mba 01/2016
#

myTest: myTestMake
	@# Comment exécuter le programme myTestMake
	@echo
	@echo "vous pouvez maintenant exécuter votre programme TestMake2 avec un paramètre numérique."
	@echo
	@echo "par exemple : ./myTestMake 3"

boucle.o: boucle.c
	gcc -std=c99 -Wall -pedantic $< -c -o $@

TestMake2.o: TestMake2.c MonInclude.h boucle.h
	gcc -std=c99 -Wall -pedantic TestMake2.c -c -o $@

myTestMake: TestMake2.o boucle.o	
	gcc TestMake2.o boucle.o -o $@

clean:
	@rm -f myTestMake *.o *~ 