PROGS = member1_array member1_struct

all : $(PROGS)

% : %.c
	gcc -g -o $@ $^

clean:
	rm -f $(PROGS) *~
