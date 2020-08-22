PROGS = hello args cat cp wcount 

all : $(PROGS)

% : %.c
	gcc -g -o $@ $^

clean:
	rm -f $(PROGS) *~

