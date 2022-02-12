
all: producer consumer destroyer

produce: producer
	@./producer

producer: producer.o sem_util.o shm_util.o
	gcc $^ -o $@  

producer.o: producer.c
	gcc $< -c -o $@  


consume: consumer
	@./consumer

consumer: consumer.o sem_util.o shm_util.o
	gcc $^ -o $@  

consumer.o: consumer.c
	gcc $< -c -o $@  


sem_util.o: sem/sem_util.c sem/sem_util.h
	gcc $< -c -o $@  

shm_util.o: shm/shm_util.c shm/shm_util.h
	gcc $< -c -o $@  


destroy: destroyer
	./destroyer

destroyer: destroy.c sem_util.o shm_util.o
	gcc $^ -o $@  

clean: destroy
	rm -f  producer consumer destroyer *.o ~*