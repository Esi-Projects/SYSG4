read: conf_reader.o
	@./conf_reader.o

conf_reader.o: conf_reader.c
	@gcc $< -o $@
	chmod 4755 $@

clean:
	rm -f *.o ~*