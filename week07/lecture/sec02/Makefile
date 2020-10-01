PROGS = main

OBJS = in_range_c.o in_range_s.o count_zeros_c.o count_zeros_s.o \
	   sum_array_c.o sum_array_s.o add4_s.o strlen_c.o strlen_s.o \
	   fact_c.o fact_s.o

CFLAGS = -g

%.o : %.s
	as ${CFLAGS} -o $@ $^

all : ${PROGS}

main : main.c ${OBJS}
	gcc ${CFLAGS} -o $@ $^

clean :
	rm -rf ${PROGS} ${OBJS} *~
