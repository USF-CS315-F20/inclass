PROGS = first_c first_s hello_c hello_s add_main mul_main max_main

OBJS = first_c.o first_s.o add_c.o add_s.o mul_c.o mul_s.o \
       max_c.o max_s.o

CFLAGS = -g

all : ${PROGS}

add_main : add_main.c add_c.o add_s.o
	gcc ${CFLAGS} -o $@ $^

mul_main : mul_main.c mul_c.o mul_s.o
	gcc ${CFLAGS} -o $@ $^	

max_main : max_main.c max_c.o max_s.o
	gcc ${CFLAGS} -o $@ $^		


clean :
	rm -rf ${PROGS} ${OBJS} *~
