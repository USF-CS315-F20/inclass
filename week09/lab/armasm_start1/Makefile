PROG = project04
OBJS = armasm.o scan.o parse.o codegen.o
HEADERS = armasm.h

CFLAGS = -g

all : ${PROG}

${PROG} : ${OBJS} ${HEADERS}
	gcc ${CFLAGS} -o $@ ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS} *~ *.dSYM *.o *.hex

