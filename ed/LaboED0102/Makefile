

read: guid_reader.o
	@./guid_reader.o /dev/sdc

guid_reader.o: guid_reader.c 
	gcc $< -o $@

clean:
	@rm -f *.o *~
