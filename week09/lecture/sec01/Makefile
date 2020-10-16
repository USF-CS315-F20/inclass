PROGS = week09

OBJS = add_s.o max2_s.o

CFLAGS = -g
ASFLAGS = -g

%.o : %.s
	as ${ASLAGS} -o $@ $^

all : ${PROGS}

week09 : week09.c ${OBJS}
	gcc ${CFLAGS} -o $@ $^

clean :
	rm -rf ${PROGS} ${OBJS} *~
