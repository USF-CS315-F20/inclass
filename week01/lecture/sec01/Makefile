PROGS = cat cp wcount

all : $(PROGS)

%.o : %.c
	gcc -g -c -o $@^

% : %.o
	gcc -g -o $@^

clean:
	rm -f $(PROGS) *~

