PROGS = week08

OBJS = sum_array_rec_c.o sum_array_rec_s.o strcat_c.o strcat_s.o \
       substr_c.o substr_s.o

CFLAGS = -g

%.o : %.s
	as ${CFLAGS} -o $@ $^

all : ${PROGS}

week08 : week08.c ${OBJS}
	gcc ${CFLAGS} -o $@ $^

clean :
	rm -rf ${PROGS} ${OBJS} *~
