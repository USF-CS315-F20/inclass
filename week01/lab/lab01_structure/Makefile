PROGS = replace map_test

all : $(PROGS)

map_test : map_test.c map.c map.h
	gcc -o $@ map_test.c map.c

replace : replace.c map.c map.h
	gcc -o $@ replace.c map.c

clean:
	rm -rf $(PROG) *~
