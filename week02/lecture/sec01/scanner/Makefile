PROGS = scan1 scan2

all : $(PROGS)

% : %.c
	gcc -g -o $@ $^

clean:
	rm -f $(PROGS) *~
