PROGS = add4_main quadratic_main min_main

OBJS = add4_c.o add4_s.o quadratic_c.o quadratic_s.o min_c.o min_s.o

CFLAGS = -g

all : ${PROGS}

add4_main : add4_main.c add4_c.o add4_s.o
	gcc ${CFLAGS} -o $@ $^

quadratic_main : quadratic_main.c quadratic_c.o quadratic_s.o
	gcc ${CFLAGS} -o $@ $^

min_main : min_main.c min_c.o min_s.o
	gcc ${CFLAGS} -o $@ $^


clean :
	rm -rf ${PROGS} ${OBJS} *~
