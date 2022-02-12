#NOM : Makefile
#CLASSE : Intro - LaboIntro 01 -01
#OBJET : autour du Makefile
#HOWTO : make ; make clean
#AUTEUR : Ayoub Lahyaoui

douche: douche.o
	@ ./douche.o

douche.o : douche.c
	gcc $< -o $@

clean:
	@ rm -f douche.o *~