PROGS = week09

OBJS = add_s.o

CFLAGS = -g

%.o : %.s
	as ${CFLAGS} -o $@ $^

all : ${PROGS}

week09 : week09.c ${OBJS}
	gcc ${CFLAGS} -o $@ $^

clean :
	rm -rf ${PROGS} ${OBJS} *~
