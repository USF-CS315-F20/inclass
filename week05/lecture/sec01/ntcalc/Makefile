PROG = lab04
OBJS = scan.o parse.o eval.o ntcalc.o conv.o
HEADERS = ntcalc.h

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c
	gcc ${CFLAGS} -c -o $@ $<

all : ${PROG}

${PROG} : ${OBJS} ${HEADERS}
	gcc ${CFLAGS} -o $@ ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS} *~ *.dSYM

