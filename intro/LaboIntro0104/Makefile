#NOM    : Makefile
#CLASSE : Intro - LaboIntro 01-04
#OBJET  : demo du programme Mecho.c
#HOWTO	: make; make clean
#AUTEUR	: MBA 08/2016          

demo:	Mecho Demo
	@clear
	@./Demo

Mecho: Mecho.c 
	gcc -std=c99  -pedantic $< -o $@

clean:
	rm -f Mecho fichier *~
