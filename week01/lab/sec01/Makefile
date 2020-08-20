PROGS = member1_array member1_struct

all : $(PROGS)

%.o: %.c
	gcc -g -c -o $@ $^

% : %.o
	gcc -g -o $@^

clean:
	rm -f $(PROGS) *~
