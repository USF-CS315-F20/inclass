PROGS = main

all : $(PROGS)

main : main.c foo.c
	gcc -g -o $@ $^

clean:
	rm -f $(PROGS) *~
