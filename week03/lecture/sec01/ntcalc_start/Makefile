PROGS = lab03 
OBJS = scan.o parse.o

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -o $@ $<


all : ${PROGS}

lab03 : ntcalc.h ntcalc.c scan.o parse.o
	gcc ${CFLAGS} -o $@ ntcalc.c scan.o parse.o

clean :
	rm -rf ${PROGS} ${OBJS} *~ *.dSYM

