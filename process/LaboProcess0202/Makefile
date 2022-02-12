make_zombie: zombie_maker.o
	@./zombie_maker.o

zombie_maker.o:zombie_maker.c 
	@gcc $< -o $@

double_fork: double_fork.o
	@./double_fork.o

double_fork.o:double_fork.c 
	@gcc $< -o $@

clean: 
	@rm -f *.o ~*