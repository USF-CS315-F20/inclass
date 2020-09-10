PROGS = lab03 
OBJS = scan.o parse.o eval.o

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -o $@ $<


all : ${PROGS}

lab03 : ntcalc.h ntcalc.c scan.o parse.o eval.o
	gcc ${CFLAGS} -o $@ ntcalc.c scan.o parse.o eval.o

clean :
	rm -rf ${PROGS} ${OBJS} *~ *.dSYM

