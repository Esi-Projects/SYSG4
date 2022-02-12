

all: printA printB
	./printA & ./printB

printA: printA.o sem_util.o
	gcc $^ -o $@

printB: printB.o sem_util.o
	gcc $^ -o $@


printA.o: printA.c
	gcc $< -c -o $@

printB.o: printB.c
	gcc $< -c -o $@

sem_util.o: sem/sem_util.c sem/sem_util.h
	gcc $< -c -o  $@

clean:
	rm -f printA printB *.o ~*