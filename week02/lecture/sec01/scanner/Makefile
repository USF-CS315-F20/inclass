PROGS = scan1 scan2

CFLAGS = -g

all : $(PROGS)

% : %.c
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS) *~
