

read: mbr_reader.o
	@./mbr_reader.o /dev/sdc

mbr_reader.o: mbr_reader.c 
	gcc $< -o $@

clean:
	@rm -f *.o *~